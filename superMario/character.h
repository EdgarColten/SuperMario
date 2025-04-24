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
    void setCastle(QLabel* c);
    void setBackground(QLabel* bg);
    int isHit = 0;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override; // 👈 ADD THIS!

signals:
    void gameOver();

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

    QLabel* background = nullptr;

    QLabel* castle = nullptr;
    QList<Block*> blockList;
    QList<Mushroom*> mushroomList;

    QList<Flag*> flagList;
    bool frozen = false;
    bool isWalkingRight = false;
    Flag *flag = nullptr;

    QList<Goomba*> goombaList;
    QList<Koopa*> koopaList;
    QList<Pipe*> pipeList;

    QSet<int> keysPressed; // 👈 ADD THIS!

    QMovie* walkRightMovie;
    QMovie* walkLeftMovie;
    QPixmap stillPixmapRight;
    QPixmap stillPixmapLeft;

    enum Direction { NONE, LEFT, RIGHT };
    Direction currentDirection;

    bool marioHitsMushroom(Mushroom *m);

    bool marioBottomTouchesGoombaTop(Goomba *g);
    bool marioBottomTouchesKoopaTop(Koopa *k);

    bool marioHitsGoombaFront(Goomba *g);
    bool marioHitsKoopaFront(Koopa *k);

    int stage = 1; // 1 = small, 2 = big

    void makeInvincible(); // Make Mario invincible for a short time
    void endInvincibility(); // Ends invincibility after timer

    bool invincible;  // Flag to check if Mario is invincible
    QTimer *invincibilityTimer;  // Timer to handle invincibility duration

};

#endif // CHARACTER_H
