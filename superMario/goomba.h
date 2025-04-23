#ifndef GOOMBA_H
#define GOOMBA_H

#include <QLabel>
#include <QMovie>
#include <QTimer>
#include "pipe.h"

class Goomba : public QLabel
{
    Q_OBJECT

public:
    explicit Goomba(const QString &goombaImagePath, QWidget *parent = nullptr);
    void stomp();
    bool isStomped() const;
    void setPipes(const QList<Pipe *> &pipeList);

private slots:
    void moveWalk();

private:
    QMovie *movie;
    QString imagePath;
    QTimer *moveTimer;
    int speed;
    int direction;
    bool stomped;
    QList<Pipe *> pipes;

    void flipSprite();
};

#endif // GOOMBA_H
