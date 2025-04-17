#ifndef CHARACTER_H
#define CHARACTER_H

#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include "Block.h"
#include "ItemBlock.h"
#include "goomba.h"
#include "koopa.h"
#include "pipe.h"

class Character : public QLabel
{
    Q_OBJECT
public:
    explicit Character(QWidget *parent = nullptr);
    void setBlocks(const QList<Block*> &blocks);
    void setGoombas(const QList<Goomba*>& gList);
    void setKoopas(const QList<Koopa*>& kList);
    void setPipes(const QList<Pipe*>& pList);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateMovement();

private:
    QList<Block*> blockList;
    int verticalVelocity;   // Vertical movement (positive = falling)
    int horizontalSpeed;    // Horizontal step size
    bool onGround;          // Whether Mario is standing on a block
    QTimer *movementTimer;  // Timer for updating movement (gravity & collisions)
    QList<Goomba*> goombaList;
    QList<Koopa*> koopaList;
    QList<Pipe*> pipeList;
    void applyGravity();
    void checkCollisions();
    bool marioBottomTouchesGoombaTop(Goomba *g);
    bool marioBottomTouchesKoopaTop(Koopa *k);
};

#endif // CHARACTER_H
