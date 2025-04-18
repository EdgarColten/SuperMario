#ifndef fLAG_H
#define fLAG_H

#include <QLabel>
#include <QTimer>
#include <QDebug>

class Flag : public QLabel
{
    Q_OBJECT
public:
    explicit Flag(const QString &imagePath, QWidget *parent = nullptr);
    QRect getHitBox() const;

signals:
    void levelCompleted();
    void transitionToNextLevel();
public slots:
    void levelCompletedHandler(const QString &levelName, int lives);
private:
    QLabel *completionBanner = nullptr;
    QWidget *overlay = nullptr;

};

#endif // fLAG_H
