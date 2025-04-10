#include "mushroom.h"
#include <QLabel>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMouseEvent>

Mushroom::Mushroom(const QString &imagePath, QWidget *parent) : QLabel(parent)
{
    QPixmap pix(imagePath);
    // Scale the image to a fixed size (50x50 pixels)
    setPixmap(pix.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(50, 50);
}

void Mushroom::mushroomHit()
{
    if (activated)
        return;

    activated = true;

    // Create the mushroom item label
    QLabel *itemLabel = new QLabel(parentWidget());
    QPixmap pix(itemImagePath);
    itemLabel->setPixmap(pix.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    itemLabel->setFixedSize(30, 30);

    // Position the item at the center of the block (starting at the block's top edge)
    int startX = x() + (width() - itemLabel->width()) / 2;
    int startY = y() - itemLabel->height(); // final position above the block
    itemLabel->move(startX, y()); // Initially, the item is hidden inside the block
    itemLabel->show();

    // Animate the mushroom popping upward
    QPropertyAnimation *anim = new QPropertyAnimation(itemLabel, "pos");
    anim->setDuration(500);
    anim->setStartValue(QPoint(startX, y()));
    anim->setEndValue(QPoint(startX, startY));
    anim->setEasingCurve(QEasingCurve::OutBounce);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
