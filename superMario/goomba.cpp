#include "goomba.h"

Goomba::Goomba(const QString &goombaImagePath, QWidget *parent)
    : QLabel(parent), movie(new QMovie(goombaImagePath))
{
    // Loading GIF
    this->setMovie(movie);
    this->setAlignment(Qt::AlignCenter);
    movie->start();
    movie->setScaledSize(movie->frameRect().size() / 1.5);
    this->resize(movie->frameRect().size());

    // Connecting GIF to timer
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Goomba::moveLeft);
    moveTimer->start(20); // ~60 FPS

    //Movement speed
    speed = 2;

    // Delete image when goomba is stomped
    deathTimer = new QTimer(this);
    deathTimer->setSingleShot(true);
    connect(deathTimer, &QTimer::timeout, this, [this]() {
        this->deleteLater(); // safe deletion
    });

    stomped = false;
}

void Goomba::moveLeft()
{
    int nextX = x() - speed;

    // Predict future geometry after moving
    QRect futureBounds = this->geometry();
    futureBounds.moveLeft(nextX); // Shift entire bounding box to predicted x position

    // Check for pipe collision
    for (Pipe *pipe : pipes) {
        if (futureBounds.intersects(pipe->geometry())) {
            speed *= -1;  // Reverse direction
            return;
        }
    }

    // Move to next position if no collision
    move(nextX, y());


}






void Goomba::stomp() {
    if(stomped) {
        return;
    }
    stomped = true;
    moveTimer->stop();

    // Change to stomped image
    setMovie(nullptr);
    //setPixmap(QPixmap(":/images/stompedGoomba.png").scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPixmap original(":/images/stompedGoomba.png");
    QPixmap scaled = original.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a blank image (e.g., 60x60)
    QPixmap shifted(60, 68);
    shifted.fill(Qt::transparent);

    // Draw the image with an offset (e.g., 15 px down)
    QPainter painter(&shifted);
    painter.drawPixmap(15, 30, scaled); // x = 15, y = 30
    painter.end();

    setPixmap(shifted);
    deathTimer->start(500); // wait half a second, then remove
}

bool Goomba::isStomped() const {
    return stomped;
}

void Goomba::setPipes(const QList<Pipe*> &pipeList) {
    pipes = pipeList;
}

