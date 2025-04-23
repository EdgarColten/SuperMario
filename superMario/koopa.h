#ifndef KOOPA_H
#define KOOPA_H

#include <QLabel>
#include <QMovie>
#include <QTimer>
#include "pipe.h"

class Koopa : public QLabel
{
    Q_OBJECT

public:
    explicit Koopa(const QString &koopaImagePath, QWidget *parent = nullptr);
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
    bool sliding;
    QList<Pipe *> pipes;

    void flipSprite();
};

#endif // KOOPA_H
