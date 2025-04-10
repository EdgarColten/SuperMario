#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QList>

class Mushroom : public QLabel
{
    Q_OBJECT;
public:

    explicit Mushroom(const QString &imagePath, QWidget *parent = nullptr);
    void mushroomHit(); // Call this when the mushroom is hit
private:
    QString itemImagePath;
    bool activated;


};

#endif // MUSHROOM_H
