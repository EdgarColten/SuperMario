#include "pipe.h"

Pipe::Pipe(const QString &imagePath, QWidget *parent) : QLabel(parent)
{
    QPixmap pix(imagePath);
    setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(100, 100);
}
