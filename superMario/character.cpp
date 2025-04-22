#include "character.h"
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

void Character::setMush(const QList<Mushroom *> &mushrooms)
{
    mushroomList = mushrooms;
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

void Character::setCastle(QLabel *c)
{
    castle = c;
}

void Character::setFlag(const QList<Flag*> &f)
{
    flagList = f;
}

void Character::freeze()
{
    frozen = true;
}
void Character::unfreeze()
{
    frozen = false;
}

void Character::keyPressEvent(QKeyEvent *event)
{
    if (frozen) return;

    int newX = x();
    int newY = y();

    keysPressed.insert(event->key());
    if(event->key() == Qt::Key_Left)
    {
        newX -= horizontalSpeed;
    }
    else if(event->key() == Qt::Key_Right)
    {
        newX += horizontalSpeed;
    }
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
    QRect charRect = geometry();
    bool landed = false;
    // ----- HORIZONTAL MOVEMENT -----
    int dx = 0;
    if (keysPressed.contains(Qt::Key_Left))
        dx -= horizontalSpeed;
    if (keysPressed.contains(Qt::Key_Right))
        dx += horizontalSpeed;

    // Move horizontally and immediately check for horizontal collisions.
//    int newX = x() + dx; Old movement Code(Return if new doesnt work)
//    move(newX, y());

    int newX = x();
    const int halfway = 400;

    if (dx > 0 && x() >= halfway){
        for (Block *block : blockList)
            block->move(block->x() - dx, block->y());
        for (Mushroom *mushroom : mushroomList)
            mushroom->move(mushroom->x() - dx, mushroom->y());
        for (Goomba *goomba : goombaList)
            goomba->move(goomba->x() - dx, goomba->y());
        for (Koopa *koopa : koopaList)
            koopa->move(koopa->x() - dx, koopa->y());
        for (Pipe *pipe : pipeList)
            pipe->move(pipe->x() - dx, pipe->y());
        for (Flag *flag : flagList)
            flag->move(flag->x() - dx, flag->y());
        castle->move(castle->x() - dx, castle->y());
    }
    else if( dx < 0 && x() <= 0){}

    else {
        move(newX+dx,y());
    }

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
                if (ib){
                    ib->hit();
                    Mushroom *mushroom = new Mushroom(":/images/mushroom.png",parentWidget());
                    mushroom->move(block->x()+10, block->y()-40);
                    mushroom->show();
                    mushroomList.append(mushroom);

                }
            }
        }
    }

    for (int i = 0; i < mushroomList.size(); ++i) {
        Mushroom* m = mushroomList[i];


        if (marioHitsMushroom(m)) {
            setPixmap(QPixmap(":/images/mario.png").scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            setFixedSize(60, 60);

            move(x(),y() - 20);
            m->deleteLater();
            mushroomList.removeAt(i); // remove after stomp
            continue;
        }
    }
    for (int i = 0; i < goombaList.size(); ++i) {
        Goomba* g = goombaList[i];

        // Check if it's already stomped
        if (g->isStomped()) {
            goombaList.removeAt(i);  // remove from list
            continue; // don't increment i, list is now shorter
        }

        if (marioBottomTouchesGoombaTop(g)) {
            g->stomp();
            verticalVelocity = -10; // bounce Mario up
            goombaList.removeAt(i); // remove after stomp
            continue;
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

    for(Flag* flag : flagList)
    {
        QRect flagRect = flag->geometry();

        if(charRect.right()-90>= flagRect.left())
        {
            emit flag->levelCompleted();
        }
    }

    // If vertical velocity remains non-zero, Mario is in the air.
    if (verticalVelocity != 0)
        onGround = false;
}

bool Character::marioHitsMushroom(Mushroom *m)
{
    QRect marioRect = this->geometry();
    QRect mushRect = m->geometry();

    return marioRect.intersects(mushRect);
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

