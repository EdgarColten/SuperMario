#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "Block.h"
#include "ItemBlock.h"
#include "Character.h"
#include "Koopa.h"
#include "Goomba.h"
#include "Pipe.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createLevel();
    QList<Block*> blocks; // All blocks that form the level
    QList<Goomba*> goombas;
    QList<Koopa*> koopas;
    QList<Pipe*> pipes;
    Character *mario;
};

#endif // MAINWINDOW_H
