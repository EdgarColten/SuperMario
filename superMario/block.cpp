#include "Block.h"

Block::Block(const QString &imagePath, QWidget *parent) : QLabel(parent)
{
    QPixmap pix(imagePath);
    // Scale the image to a fixed size (50x50 pixels)
    setPixmap(pix.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(50, 50);
}
