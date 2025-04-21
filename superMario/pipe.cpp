#include "pipe.h"

Pipe::Pipe(const QString &imagePath, QWidget *parent) : QLabel(parent)
{
    QPixmap pix(imagePath);
    setPixmap(pix.scaled(80, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(80, 100);
}
