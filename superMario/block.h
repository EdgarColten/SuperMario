#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>

class Block : public QLabel
{
    Q_OBJECT
public:
    explicit Block(const QString &imagePath, QWidget *parent = nullptr);
};

#endif // BLOCK_H
