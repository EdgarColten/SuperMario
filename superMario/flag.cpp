#include "flag.h"
#include <QPixmap>

Flag::Flag(const QString &imagePath, QWidget *parent)
    : QLabel(parent)
{
    QPixmap pix(imagePath);
    setPixmap(pix.scaled(100,400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setFixedSize(100, 400);
}
QRect Flag::getHitBox() const
{
    QRect rect = geometry();
    rect.adjust(-10, 0, 10, 0);  // Slightly widen hitbox
    return rect;
}

void Flag::levelCompletedHandler(const QString &levelName, int lives)
{
    if (!completionBanner)
    {
        overlay = new QWidget(parentWidget());
        overlay->setStyleSheet("background-color: black;");
        overlay->setGeometry(parentWidget()->rect());
        overlay->show();

        completionBanner = new QLabel(overlay);
        completionBanner->setText(QString("World %1\nLives: %2").arg(levelName).arg(lives));
        completionBanner->setStyleSheet("QLabel { background-color: rgba(0, 0, 0, 180); color: white; font-size: 24px; border: 2px solid white; padding: 20px; }");
        completionBanner->setAlignment(Qt::AlignCenter);
        completionBanner->setFixedSize(300, 150);

        int x = (parentWidget()->width() - completionBanner->width()) / 2;
        int y = (parentWidget()->height() - completionBanner->height()) / 2;
        completionBanner->move(x, y);
        completionBanner->show();

        QTimer::singleShot(2000, this, [this]() {
            if (completionBanner) {
                completionBanner->deleteLater();
                completionBanner = nullptr;
            }
            if (overlay) {
                overlay->deleteLater();
                overlay = nullptr;
            }
            emit transitionToNextLevel();
        });
    }

}
