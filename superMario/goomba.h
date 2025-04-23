#ifndef GOOMBA_H
#define GOOMBA_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMovie>
#include <QTimer>

class Goomba : public QLabel
{
    Q_OBJECT
public:
    explicit Goomba(const QString &goombaImagePath, QWidget *parent = nullptr);
    void moveLeft();
    void stomp();
    bool isStomped() const;

private:
    QLabel *label;
    QMovie *movie;
    QTimer *moveTimer;
    int speed;
    QTimer *deathTimer;
    bool stomped;
};

#endif // GOOMBA_H
