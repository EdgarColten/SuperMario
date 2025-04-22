#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

#include "Block.h"
#include "itemBlock.h"
#include "character.h"
#include "mushroom.h"
#include "koopa.h"
#include "goomba.h"
#include "pipe.h"
#include "flag.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLabel *castle;

public slots:
    void startNextLevel();

private:
    void createLevel();

    QList<Block*> blocks; // All blocks that form the level
    QList<Mushroom*> mushrooms; // All blocks that form the level
    QList<Goomba*> goombas;
    QList<Koopa*> koopas;
    QList<Pipe*> pipes;
    QList<Flag*> flag;

    Character *mario;
};

#endif // MAINWINDOW_H
