#ifndef CHARACTER_H
#define CHARACTER_H

#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QSet>

#include "block.h"
#include "itemBlock.h"
#include "mushroom.h"
#include "goomba.h"
#include "koopa.h"
#include "pipe.h"
#include "flag.h"

class Character : public QLabel
{
    Q_OBJECT

public:

    explicit Character(QWidget *parent = nullptr);

    void setFlag(const QList<Flag*> &f);
    void freeze();
    void unfreeze();

    void setBlocks(const QList<Block*> &blocks);
    void setMush(const QList<Mushroom*> &mushrooms);
    void setGoombas(const QList<Goomba*>& gList);
    void setKoopas(const QList<Koopa*>& kList);
    void setPipes(const QList<Pipe*>& pList);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override; // 👈 ADD THIS!

private slots:
    void updateMovement();

private:
    void applyGravity();
    void checkCollisions();

    void checkHorizontalCollisions();
    void checkVerticalCollisions();


    QTimer *movementTimer;
    int verticalVelocity;
    int horizontalSpeed;
    bool onGround;

    QList<Block*> blockList;
    QList<Mushroom*> mushroomList;

    QList<Flag*> flagList;
    bool frozen = false;
    Flag *flag = nullptr;

    QList<Goomba*> goombaList;
    QList<Koopa*> koopaList;
    QList<Pipe*> pipeList;

    QSet<int> keysPressed; // 👈 ADD THIS!

    bool marioHitsMushroom(Mushroom *m);

    bool marioBottomTouchesGoombaTop(Goomba *g);
    bool marioBottomTouchesKoopaTop(Koopa *k);

};

#endif // CHARACTER_H
