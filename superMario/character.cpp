#include "character.h"
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>

Character::Character(QWidget *parent)
    : QLabel(parent), verticalVelocity(0), horizontalSpeed(10), onGround(false)
{
    // setPixmap(QPixmap(":/images/marioOG.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(40, 40);
    setFocusPolicy(Qt::StrongFocus);

    stillPixmapRight = QPixmap(":/images/marioOG.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    stillPixmapLeft = QPixmap(":/images/marioLeftOG.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(stillPixmapRight);
    currentDirection = NONE;

    walkRightMovie = new QMovie(":/images/marioWalking.gif");
    walkLeftMovie = new QMovie(":/images/marioWalkingLeft.gif");

    walkRightMovie->setScaledSize(QSize(40, 40));
    walkLeftMovie->setScaledSize(QSize(40, 40));

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Character::updateMovement);
    movementTimer->start(30);

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

    if (event->key() == Qt::Key_Right && currentDirection != RIGHT)
    {
        setMovie(walkRightMovie);
        walkRightMovie->start();
        currentDirection = RIGHT;
    }

    if (event->key() == Qt::Key_Left && currentDirection != LEFT)
    {
        setMovie(walkLeftMovie);
        walkLeftMovie->start();
        currentDirection = LEFT;
    }

    if (event->key() == Qt::Key_Space && onGround)
    {
        verticalVelocity = -20;
        onGround = false;
    }
}

void Character::keyReleaseEvent(QKeyEvent *event)
{
    keysPressed.remove(event->key());

    if ((event->key() == Qt::Key_Right && currentDirection == RIGHT) ||
        (event->key() == Qt::Key_Left && currentDirection == LEFT))
    {
        setMovie(nullptr);
        if (currentDirection == RIGHT)
            setPixmap(stillPixmapRight);
        else
            setPixmap(stillPixmapLeft);

        currentDirection = NONE;
    }
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
                if (ib && isHit == 0){
                    ib->hit();
                    isHit++;
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
            stillPixmapRight = QPixmap(":/images/bigMario.png").scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            stillPixmapLeft = QPixmap(":/images/bigMarioLeft.png").scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            delete walkRightMovie;
            delete walkLeftMovie;

            walkRightMovie = new QMovie(":/images/bigMarioWalking.gif");
            walkLeftMovie = new QMovie(":/images/bigMarioWalkingLeft.gif");

            walkRightMovie->setScaledSize(QSize(60, 60));
            walkLeftMovie->setScaledSize(QSize(60, 60));

            setPixmap(stillPixmapRight);
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
