#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Super Mario - Main Menu");
    setFixedSize(800, 600);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *bg = new QLabel(this);
    bg->setPixmap(QPixmap(":/images/titleBG1.png").scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    bg->setFixedSize(this->size());
    bg->lower();

    QLabel *logo = new QLabel(this);
    logo->setPixmap(QPixmap(":/images/marioLogo.png").scaled(600,200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    logo->setFixedSize(600,200);
    logo->move(100,0);

    QPushButton *startButton = new QPushButton(this);
    startButton->setFixedSize(300,100);
    startButton->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   background-color: transparent;"
        "   background-image: url(:/images/startBut.png);"
        "   background-repeat: no-repeat;"
        "   background-position: center;"
        "}"
        "QPushButton:hover {"
        "   background-image: url(:/images/startBut1.jpg);"
        "}"
    );

    startButton->move(400,300);

    connect(startButton, &QPushButton::clicked, this, &MainMenu::startGame);

    QPushButton *exitButton = new QPushButton(this);
    exitButton->setFixedSize(300,100);
    exitButton->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   background-color: transparent;"
        "   background-image: url(:/images/exitBut.jpg);"
        "   background-repeat: no-repeat;"
        "   background-position: center;"
        "}"
        "QPushButton:hover {"
        "   background-image: url(:/images/exitBut1.jpg);"
        "}"
    );

    exitButton->move(400,450);

    connect(exitButton, &QPushButton::clicked, this, []() {
        QApplication::quit();
    });
}
