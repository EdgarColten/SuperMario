#ifndef ITEMBLOCK_H
#define ITEMBLOCK_H

#include "Block.h"
#include <QPropertyAnimation>

class ItemBlock : public Block
{
    Q_OBJECT
public:
    explicit ItemBlock(const QString &blockImagePath, const QString &itemImagePath, QWidget *parent = nullptr);
    void hit(); // Call this when the block is hit

protected:
    // For demonstration, clicking on the block will trigger the hit:
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool activated;
    QString itemImagePath;
};

#endif // ITEMBLOCK_H
