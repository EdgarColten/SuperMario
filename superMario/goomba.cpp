#include "Goomba.h"
#include <QPainter>
#include <QTransform>

Goomba::Goomba(const QString &goombaImagePath, QWidget *parent)
    : QLabel(parent), movie(new QMovie(goombaImagePath)), imagePath(goombaImagePath)
{
    this->setMovie(movie);
    this->setAlignment(Qt::AlignCenter);
    movie->start();
    movie->setScaledSize(movie->frameRect().size() / 1.25);
    this->resize(movie->frameRect().size());

    speed = 2;
    direction = -1; // Start moving left
    stomped = false;

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Goomba::moveWalk);
    moveTimer->start(20);
}

void Goomba::setPipes(const QList<Pipe *> &pipeList) {
    this->pipes = pipeList;
}

void Goomba::moveWalk()
{
    if (stomped) return;

    int newX = x() + speed * direction;
    QRect futureRect(newX, y(), width(), height());

    for (Pipe *pipe : pipes) {
        if (futureRect.intersects(pipe->geometry())) {
            direction *= -1;
            flipSprite();
            return;
        }
    }

    move(newX, y());

    if (x() + width() < 0 || x() > parentWidget()->width()) {
        moveTimer->stop();
    }
}

void Goomba::flipSprite()
{
    movie->stop();
    QMovie *newMovie = new QMovie(imagePath);
    newMovie->setScaledSize(movie->scaledSize());
    newMovie->start();

    if (direction == 1) {
        // Flip right
        QImage img = newMovie->currentImage().mirrored(true, false);
        QLabel::setPixmap(QPixmap::fromImage(img));
    } else {
        // Normal
        this->setMovie(newMovie);
    }

    delete movie;
    movie = newMovie;
}

void Goomba::stomp()
{
    if (stomped) return;

    stomped = true;
    speed = 0;
    moveTimer->stop();

    setMovie(nullptr);
    QPixmap original(":/images/stompedGoomba.png");
    QPixmap scaled = original.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap shifted(60, 68);
    shifted.fill(Qt::transparent);

    QPainter painter(&shifted);
    painter.drawPixmap(10, 30, scaled);
    painter.end();

    setPixmap(shifted);
}

bool Goomba::isStomped() const {
    return stomped;
}
