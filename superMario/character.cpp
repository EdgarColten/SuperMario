#include "Character.h"
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>

Character::Character(QWidget *parent)
    : QLabel(parent), verticalVelocity(0), horizontalSpeed(10), onGround(false)
{
    // Set Mario's image (adjust path/size as needed)
    setPixmap(QPixmap(":/images/mario.png")
                  .scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(40, 40);
    setFocusPolicy(Qt::StrongFocus);

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Character::updateMovement);
    movementTimer->start(30);
}

void Character::setBlocks(const QList<Block*> &blocks)
{
    blockList = blocks;
}

void Character::keyPressEvent(QKeyEvent *event)
{
    keysPressed.insert(event->key());
    // Jump if on ground
    if (event->key() == Qt::Key_Space && onGround)
    {
        verticalVelocity = -20; // Jump impulse
        onGround = false;
    }
}

void Character::keyReleaseEvent(QKeyEvent *event)
{
    keysPressed.remove(event->key());
}

void Character::updateMovement()
{
    // ----- HORIZONTAL MOVEMENT -----
    int dx = 0;
    if (keysPressed.contains(Qt::Key_Left))
        dx -= horizontalSpeed;
    if (keysPressed.contains(Qt::Key_Right))
        dx += horizontalSpeed;

    // Move horizontally and immediately check for horizontal collisions.
    int newX = x() + dx;
    move(newX, y());
    for (Block* block : blockList)
    {
        if (geometry().intersects(block->geometry()))
        {
            // If moving right, snap to the left edge of the block.
            if (dx > 0)
            {
                move(block->x() - width(), y());
            }
            // If moving left, snap to the right edge of the block.
            else if (dx < 0)
            {
                move(block->x() + block->width(), y());
            }
        }
    }

    // ----- VERTICAL MOVEMENT -----
    // Record Y before applying gravity.
    int oldY = y();
    verticalVelocity += 1;  // Apply gravity (or reduce upward velocity)
    int newY = y() + verticalVelocity;
    move(x(), newY);

    // Check for vertical collisions without affecting X.
    for (Block* block : blockList)
    {
        if (geometry().intersects(block->geometry()))
        {
            // If falling: land on the block's top.
            if (verticalVelocity > 0 && (oldY + height() <= block->y()))
            {
                move(x(), block->y() - height());
                verticalVelocity = 0;
                onGround = true;
            }
            // If jumping upward: head bump.
            else if (verticalVelocity < 0 && (oldY >= block->y() + block->height()))
            {
                // Place Mario so his top is exactly at the block's bottom.
                move(x(), block->y() + block->height());
                verticalVelocity = 0;  // Stop upward movement

                // Trigger the block hit if it's an item block.
                ItemBlock *ib = qobject_cast<ItemBlock*>(block);
                if (ib)
                    ib->hit();
            }
        }
    }

    // If vertical velocity remains non-zero, Mario is in the air.
    if (verticalVelocity != 0)
        onGround = false;
}
