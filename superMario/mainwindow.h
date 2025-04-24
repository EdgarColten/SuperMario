#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QPixmap>

#include "Block.h"
#include "itemBlock.h"
#include "character.h"
#include "mushroom.h"
#include "koopa.h"
#include "goomba.h"
#include "pipe.h"
#include "flag.h"
#include "mainMenu.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLabel *castle;
    void showMainMenu();
    void startGame(int level);

public slots:
    void startNextLevel();

private:
    void createLevel();
    void createLevel2();

    QLabel *gameOverBanner = nullptr;
    QWidget *overlay = nullptr;

    QList<Block*> blocks; // All blocks that form the level
    QList<Mushroom*> mushrooms; // All blocks that form the level
    QList<Goomba*> goombas;
    QList<Koopa*> koopas;
    QList<Pipe*> pipes;
    QList<Flag*> flag;
    QLabel *backgroundImage;


    Character *mario;
};

#endif // MAINWINDOW_H
