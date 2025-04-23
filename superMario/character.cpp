#include "character.h"
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>

Character::Character(QWidget *parent)
    : QLabel(parent), verticalVelocity(0), horizontalSpeed(10), onGround(false)
{
    setPixmap(QPixmap(":/images/mario.png")
                  .scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(40, 40);
    setFocusPolicy(Qt::StrongFocus);

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Character::updateMovement);
    movementTimer->start(30);

    invincibilityTimer = new QTimer(this);
    connect(invincibilityTimer, &QTimer::timeout, this, &Character::endInvincibility);
}

void Character::setBlocks(const QList<Block*> &blocks) { blockList = blocks; }
void Character::setMush(const QList<Mushroom *> &mushrooms) { mushroomList = mushrooms; }
void Character::setGoombas(const QList<Goomba*>& gList) { goombaList = gList; }
void Character::setKoopas(const QList<Koopa*>& kList) { koopaList = kList; }
void Character::setPipes(const QList<Pipe*>& pList) { pipeList = pList; }
void Character::setFlag(const QList<Flag*> &f) { flagList = f; }
void Character::setCastle(QLabel *c){ castle = c; }
void Character::freeze() { frozen = true; }
void Character::unfreeze() { frozen = false; }

void Character::keyPressEvent(QKeyEvent *event)
{
    if (frozen) return;

    keysPressed.insert(event->key());

    if (event->key() == Qt::Key_Space && onGround)
    {
        verticalVelocity = -20;
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

    int dx = 0;
    if (keysPressed.contains(Qt::Key_Left)) dx -= horizontalSpeed;
    if (keysPressed.contains(Qt::Key_Right)) dx += horizontalSpeed;

    int newX = x();
    const int halfway = 400;

    if (dx > 0 && x() >= halfway) {
        for (Block *block : blockList) block->move(block->x() - dx, block->y());
        for (Mushroom *mushroom : mushroomList) mushroom->move(mushroom->x() - dx, mushroom->y());
        for (Goomba *goomba : goombaList) goomba->move(goomba->x() - dx, goomba->y());
        for (Koopa *koopa : koopaList) koopa->move(koopa->x() - dx, koopa->y());
        for (Pipe *pipe : pipeList) pipe->move(pipe->x() - dx, pipe->y());
        for (Flag *flag : flagList) flag->move(flag->x() - dx, flag->y());
        castle->move(castle->x() - dx, castle->y());
    } else if (dx < 0 && x() <= 0) {
        // Prevent moving off the screen left
    } else {
        move(newX + dx, y());
    }

    // Horizontal collisions with blocks
    for (Block* block : blockList)
    {
        if (geometry().intersects(block->geometry()))
        {
            if (dx > 0)
                move(block->x() - width(), y());
            else if (dx < 0)
                move(block->x() + block->width(), y());
        }
    }

    // Horizontal collisions with pipes
    for (Pipe* pipe : pipeList)
    {
        if (geometry().intersects(pipe->geometry()))
        {
            if (dx > 0)
                move(pipe->x() - width(), y());
            else if (dx < 0)
                move(pipe->x() + pipe->width(), y());
        }
    }

        // Horizontal collisions with Koopas (damage handling)
    for (int i = 0; i < koopaList.size(); ++i)
    {
        Koopa* k = koopaList[i];
        if (k->isStomped()) continue; // Optional: skip if Koopa is stomped/shelled

        if (geometry().intersects(k->geometry()))
        {
            if (!marioBottomTouchesKoopaTop(k)) // horizontal collision
            {
                if (invincible) continue;

                if (stage == 2)
                {
                    stage = 1;
                    setPixmap(QPixmap(":/images/mario.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    setFixedSize(40, 40);
                    move(x(), y() + 20);
                }
                else
                {
                    //change to game over

                makeInvincible(); // Avoid repeated hits
                break;
            }
        }
    }



    // Horizontal collisions with Goombas (damage handling)
    for (int i = 0; i < goombaList.size(); ++i)
    {
        Goomba* g = goombaList[i];
        if (g->isStomped()) continue;

        if (geometry().intersects(g->geometry()))
        {
            if (!marioBottomTouchesGoombaTop(g)) // only horizontal, not stomping
            {
                if (invincible) {
                    // If Mario is invincible, don't process damage
                    continue;
                }

                if (stage == 2)
                {
                    stage = 1;
                    setPixmap(QPixmap(":/images/mario.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    setFixedSize(40, 40);
                    move(x(), y() + 20); // shrink back
                }

                else
                {
                    //change to game over
                }
                makeInvincible();  // Activate invincibility when Mario is hit
                break;
            }
        }
    }

    // ----- VERTICAL MOVEMENT -----
    int oldY = y();
    verticalVelocity += 1;
    int newY = y() + verticalVelocity;
    move(x(), newY);

    // Vertical collisions with blocks
    for (Block* block : blockList)
    {
        if (geometry().intersects(block->geometry()))
        {
            if (verticalVelocity > 0 && (oldY + height() <= block->y()))
            {
                move(x(), block->y() - height());
                verticalVelocity = 0;
                onGround = true;
            }
            else if (verticalVelocity < 0 && (oldY >= block->y() + block->height()))
            {
                move(x(), block->y() + block->height());
                verticalVelocity = 0;

                ItemBlock *ib = qobject_cast<ItemBlock*>(block);
                if (ib){
                    ib->hit();
                    Mushroom *mushroom = new Mushroom(":/images/mushroom.png", parentWidget());
                    mushroom->move(block->x() + 10, block->y() - 40);
                    mushroom->show();
                    mushroomList.append(mushroom);
                }
            }
        }
    }

    // Vertical collisions with pipes
    for (Pipe* pipe : pipeList)
    {
        if (geometry().intersects(pipe->geometry()))
        {
            if (verticalVelocity > 0 && (oldY + height() <= pipe->y()))
            {
                move(x(), pipe->y() - height());
                verticalVelocity = 0;
                onGround = true;
            }
            else if (verticalVelocity < 0 && (oldY >= pipe->y() + pipe->height()))
            {
                move(x(), pipe->y() + pipe->height());
                verticalVelocity = 0;
            }
        }
    }

    for (int i = 0; i < mushroomList.size(); ++i) {
        Mushroom* m = mushroomList[i];
        if (marioHitsMushroom(m)) {
            setPixmap(QPixmap(":/images/mario.png").scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            setFixedSize(60, 60);
            move(x(), y() - 20);
            m->deleteLater();
            mushroomList.removeAt(i);
            continue;
        }
    }

    for (int i = 0; i < goombaList.size(); ++i) {
        Goomba* g = goombaList[i];
        if (g->isStomped()) {
            goombaList.removeAt(i);
            continue;
        }

        if (marioBottomTouchesGoombaTop(g)) {
            g->stomp();
            verticalVelocity = -10;
            goombaList.removeAt(i);
            continue;
        }
    }

    for (int i = 0; i < koopaList.size(); ++i) {
        Koopa* k = koopaList[i];
        if (k->isStomped()) continue;

        if (marioBottomTouchesKoopaTop(k)) {
            k->stomp();
            verticalVelocity = -10;
            continue;
        }
    }

    for (Flag* flag : flagList)
    {
        QRect flagRect = flag->geometry();
        if (charRect.right() - 90 >= flagRect.left())
        {
            emit flag->levelCompleted();
        }
    }

    if (verticalVelocity != 0)
        onGround = false;
}

bool Character::marioHitsMushroom(Mushroom *m)
{
    QRect marioRect = this->geometry();
    QRect mushRect = m->geometry();
    return marioRect.intersects(mushRect);
}

void Character::makeInvincible()
{
    if (!invincible) {
        invincible = true;  // Set invincible flag to true
        invincibilityTimer->start(2000); // Set invincibility for 3 seconds
    }
}

void Character::endInvincibility()
{
    invincible = false;  // Set invincible flag to false after the timer ends
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
