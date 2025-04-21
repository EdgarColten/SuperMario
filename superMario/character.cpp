#include "Character.h"
#include <QPixmap>
#include <QDebug>

Character::Character(QWidget *parent) : QLabel(parent),
    verticalVelocity(0), horizontalSpeed(10), onGround(false)
{
    // Set Mario's image (adjust path/size as needed)
    setPixmap(QPixmap(":/images/mario.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(40, 40);
    setFocusPolicy(Qt::StrongFocus);

    // Timer to update gravity and check collisions (~50 FPS)
    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Character::updateMovement);
    movementTimer->start(20);
}

void Character::setBlocks(const QList<Block*> &blocks)
{
    blockList = blocks;
}

void Character::keyPressEvent(QKeyEvent *event)
{
    int newX = x();
    int newY = y();

    if(event->key() == Qt::Key_Left)
    {
        newX -= horizontalSpeed;
    }
    else if(event->key() == Qt::Key_Right)
    {
        newX += horizontalSpeed;
    }
    else if(event->key() == Qt::Key_Space)
    {
        // Jump only if on a block (platform)
        if(onGround)
        {
            verticalVelocity = -20; // Jump impulse (negative moves up)
            onGround = false;
        }
    }
    move(newX, newY);
}

void Character::updateMovement()
{
    applyGravity();
    checkCollisions();
}

void Character::applyGravity()
{
    // Apply gravity: accelerate downward
    verticalVelocity += 1;  // gravity acceleration
    int newY = y() + verticalVelocity;
    move(x(), newY);
}

void Character::checkCollisions()
{
    // Create a rectangle representing Mario's current area
    Koopa *koopa;
    Goomba *goomba;
    Pipe *pipe;
    QRect goombaRect = goomba->geometry();
    QRect pipeRect = pipe->geometry();
    QRect charRect = geometry();
    bool landed = false;

    // Loop over all blocks in the level
    for(Block* block : blockList)
    {
        QRect blockRect = block->geometry();

        // Check landing: if Mario's bottom is coming down onto a block
        // We use a tolerance (5 pixels) to decide if he is landing.
        if(charRect.intersects(blockRect))
        {
            // If falling and Mario's bottom was just above the block, he lands.
            if(verticalVelocity >= 0 && (charRect.bottom() - verticalVelocity) <= blockRect.top() &&
                charRect.bottom() >= blockRect.top() &&
                charRect.right() > blockRect.left() && charRect.left() < blockRect.right())
            {
                move(x(), blockRect.top() - height());
                verticalVelocity = 0;
                landed = true;
                onGround = true;
            }
            // Check head collision (jumping upward into a block)
            else if(verticalVelocity < 0 && (charRect.top() - verticalVelocity) >= blockRect.bottom() &&
                     charRect.top() <= blockRect.bottom() &&
                     charRect.right() > blockRect.left() && charRect.left() < blockRect.right())
            {
                // If block is an ItemBlock, trigger its hit
                ItemBlock *ib = qobject_cast<ItemBlock*>(block);
                if(ib)
                {
                    ib->hit();
                }
                // Reverse upward momentum so Mario starts falling
                verticalVelocity = 1;
            }
        }
    }

    /*for(Pipe* pipe : pipeList)
    {
        QRect pipeRect = pipe->geometry();

        // Check landing: if Mario's bottom is coming down onto a pipe
        // We use a tolerance (5 pixels) to decide if he is landing.
        if(charRect.intersects(pipeRect))
        {
            // If falling and Mario's bottom was just above the block, he lands.
            if(verticalVelocity >= 0 && (charRect.bottom() - verticalVelocity) <= pipeRect.top() &&
                charRect.bottom() >= pipeRect.top() &&
                charRect.right() > pipeRect.left() && charRect.left() < pipeRect.right())
            {
                move(x(), pipeRect.top() - height());
                verticalVelocity = 0;
                landed = true;
                onGround = true;
            }
            // Check head collision (jumping upward into a block)
            else if(verticalVelocity < 0 && (charRect.top() - verticalVelocity) >= pipeRect.bottom() &&
                     charRect.top() <= pipeRect.bottom() &&
                     charRect.right() > pipeRect.left() && charRect.left() < pipeRect.right())
            {
                // Reverse upward momentum so Mario starts falling
                verticalVelocity = 1;
            }
        }
    }*/

    for (Pipe* pipe : pipeList)
    {
        if (goombaRect.intersects(pipeRect))
        {
            if (goomba->direction > 0 &&
                goombaRect.right() > pipeRect.left() &&
                goombaRect.left() < pipeRect.left() &&
                goombaRect.bottom() > pipeRect.top() &&
                goombaRect.top() < pipeRect.bottom())
            {
                goomba->direction = -1;
                goomba->move(pipeRect.left() - goombaRect.width(), goomba->y());
            }
            else if (goomba->direction < 0 &&
                goombaRect.left() < pipeRect.right() &&
                goombaRect.right() > pipeRect.right() &&
                goombaRect.bottom() > pipeRect.top() &&
                goombaRect.top() < pipeRect.bottom())
            {
                goomba->direction = 1;
                goomba->move(pipeRect.right(), goomba->y());
            }
        }
    }

    for (int i = 0; i < koopaList.size(); ++i) {
        Koopa* k = koopaList[i];

        // Check if it's already stomped
        if (k->isStomped()) {
            continue;
        }

        // Mario stomps on Koopa
        if (marioBottomTouchesKoopaTop(k)) {
            k->stomp();
            verticalVelocity = -10;
            continue;
        }
    }
    if(!landed)
        onGround = false;
}

void Character::setGoombas(const QList<Goomba*>& gList) {
    goombaList = gList;
}

void Character::setKoopas(const QList<Koopa*>& kList) {
    koopaList = kList;
}

void Character::setPipes(const QList<Pipe*>& pList) {
    pipeList = pList;
}

bool Character::marioBottomTouchesGoombaTop(Goomba *g)
{
    QRect marioRect = this->geometry();
    QRect goombaRect = g->geometry();

    return verticalVelocity > 0 &&
           marioRect.bottom() >= goombaRect.top() - 5 &&
           marioRect.bottom() <= goombaRect.top() + 10 &&
           marioRect.right() > goombaRect.left() &&
           marioRect.left() < goombaRect.right();
}

bool Character::marioBottomTouchesKoopaTop(Koopa *k)
{
    QRect marioRect = this->geometry();
    QRect koopaRect = k->geometry();

    return verticalVelocity > 0 &&
           marioRect.bottom() >= koopaRect.top() - 5 &&
           marioRect.bottom() <= koopaRect.top() + 10 &&
           marioRect.right() > koopaRect.left() &&
           marioRect.left() < koopaRect.right();
}

