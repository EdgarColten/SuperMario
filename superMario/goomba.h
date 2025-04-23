#ifndef GOOMBA_H
#define GOOMBA_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMovie>
#include <QTimer>
#include "pipe.h"


class Goomba : public QLabel
{
    Q_OBJECT
public:
    explicit Goomba(const QString &goombaImagePath, QWidget *parent = nullptr);
    void moveLeft();
    void stomp();
    bool isStomped() const;
    void setPipes(const QList<Pipe *> &pipeList);


private:
    QLabel *label;
    QMovie *movie;
    QTimer *moveTimer;
    int speed;
    QTimer *deathTimer;
    bool stomped;
    QList<Pipe*> pipes; // Add this in private or protected
    bool movingLeft = true;

};

#endif // GOOMBA_H
