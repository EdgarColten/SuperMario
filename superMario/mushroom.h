#ifndef MUSHROOM_H
#define MUSHROOM_H


#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMovie>
#include <QTimer>



class Mushroom : public QLabel
{
    Q_OBJECT
public:
    explicit Mushroom(const QString &mushroomImagePath, QWidget *parent = nullptr);
    bool activated;

private:
    QLabel *label;
    //    void mushroomHit();
};



#endif // MUSHROOM_H
