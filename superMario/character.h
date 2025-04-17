#ifndef CHARACTER_H
#define CHARACTER_H

#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QSet>

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

    QSet<int> keysPressed; // 👈 ADD THIS!
};

#endif // CHARACTER_H
