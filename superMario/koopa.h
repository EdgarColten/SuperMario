#include "Koopa.h"
#include "character.h"
#include <QPainter>
#include <QMovie>
#include <QPixmap>
#include <QTransform>

Koopa::Koopa(const QString &koopaImagePath, QWidget *parent)
    : QLabel(parent), movie(new QMovie(koopaImagePath)), imagePath(koopaImagePath)
{
    // Setup GIF
    this->setMovie(movie);
    this->setAlignment(Qt::AlignCenter);
    movie->start();
    movie->setScaledSize(movie->frameRect().size() / 1.25);
    this->resize(movie->frameRect().size());

    // Movement & state
    speed = 2;
    direction = -1; // Start moving left
    stomped = false;
    sliding = false;

    // Timer for movement
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Koopa::moveWalk);
    moveTimer->start(20); // ~60 FPS
}

void Koopa::setPipes(const QList<Pipe *> &pipeList) {
    this->pipes = pipeList;
}

void Koopa::moveWalk()
{
    if (stomped) return;

    int newX = x() + speed * direction;
    QRect futureRect(newX, y(), width(), height());

    // Check pipe collisions
    for (Pipe *pipe : pipes) {
        if (futureRect.intersects(pipe->geometry())) {
            direction *= -1;
            flipSprite();
            return;
        }
    }

    move(newX, y());

    // Stop when off-screen
    if (x() + width() < 0 || x() > parentWidget()->width()) {
        moveTimer->stop();
    }
}

void Koopa::flipSprite() {
    movie->stop();

    QMovie *newMovie = new QMovie(imagePath);
    newMovie->setScaledSize(movie->scaledSize());
    newMovie->start();

    // Flip based on direction
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

void Koopa::stomp() {
    if(stomped) return;

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

    // Draw the image with an offset
    QPainter painter(&shifted);
    painter.drawPixmap(15, 30, scaled); // x = 15, y = 30
    painter.end();

    setPixmap(shifted);
}

bool Koopa::isStomped() const {
    return stomped;
}
