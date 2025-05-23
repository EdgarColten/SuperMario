#include "Koopa.h"
#include "character.h"

Koopa::Koopa(const QString &koopaImagePath, QWidget *parent)
    : QLabel(parent), movie(new QMovie(koopaImagePath))
{
    // Loading GIF
    this->setMovie(movie);
    this->setAlignment(Qt::AlignCenter);
    movie->start();
    movie->setScaledSize(movie->frameRect().size() / 1.25);
    this->resize(movie->frameRect().size());

    // Connecting GIF to timer
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Koopa::moveLeft);
    moveTimer->start(20); // ~60 FPS

    //Movement speed
    speed = 2;

    stomped = false;
    sliding = false;
}

void Koopa::moveLeft()
{
    // Move left by speed
    move(x() - speed, y());

    // Stop or reset when off-screen
    if (x() + width() < 0) {
        // move(parentWidget()->width(), y()); // reset to right side
        moveTimer->stop();
    }
}

void Koopa::stomp() {
    if(stomped) {
        return;
    }
    stomped = true;
    sliding = false;
    speed = 0;
    moveTimer->stop();

    // Change to stomped image
    setMovie(nullptr);
    QPixmap original(":/images/stompedKoopa.png");
    QPixmap scaled = original.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a blank image (e.g., 60x60)
    QPixmap shifted(60, 68);
    shifted.fill(Qt::transparent);

    // Draw the image with an offset (e.g., 15 px down)
    QPainter painter(&shifted);
    painter.drawPixmap(15, 30, scaled); // x = 15, y = 30
    painter.end();

    setPixmap(shifted);
}

bool Koopa::isStomped() const {
    return stomped;
}
