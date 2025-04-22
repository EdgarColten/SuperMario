#include "mushroom.h"
#include <QLabel>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMouseEvent>

Mushroom::Mushroom(const QString &mushroomimagePath, QWidget *parent) : QLabel(parent)
{
    QPixmap pix(mushroomimagePath);
    // Scale the image to a fixed size (50x50 pixels)
    setPixmap(pix.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(50, 50);
}

