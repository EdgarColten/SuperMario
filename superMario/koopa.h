#ifndef KOOPA_H
#define KOOPA_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMovie>
#include <QTimer>
#include "pipe.h"

class Character;

class Koopa : public QLabel
{
    Q_OBJECT
public:
    explicit Koopa(const QString &koopaImagePath, QWidget *parent = nullptr);
    void moveLeft();
    void stomp();
    bool isStomped() const;
    bool isSliding() const;
    void setPipes(const QList<Pipe*>& pipeList);


private:
    QLabel *label;
    QMovie *movie;
    QTimer *moveTimer;
    int speed;
    bool stomped;
    bool sliding;
    QList<Pipe*> pipes;
};

#endif // KOOPA_H
