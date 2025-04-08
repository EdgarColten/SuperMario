#ifndef CHARACTER_H
#define CHARACTER_H

#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include "Block.h"
#include "ItemBlock.h"

class Character : public QLabel
{
    Q_OBJECT
public:
    explicit Character(QWidget *parent = nullptr);
    void setBlocks(const QList<Block*> &blocks);

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
    void applyGravity();
    void checkCollisions();
};

#endif // CHARACTER_H
