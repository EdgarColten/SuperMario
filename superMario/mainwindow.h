#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QPair>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>

#include "block.h"
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

private slots:
    void onStartClicked();
    void onExitClicked();

private:
    void mainMenu();

    void createLevel();
    void createLevel2();
    void createLevel3();

    QList<Block*> blocks; // All blocks that form the level
    QList<Mushroom*> mushrooms; // All blocks that form the level
    QList<Goomba*> goombas;
    QList<Koopa*> koopas;
    QList<Pipe*> pipes;
    QList<Flag*> flag;

    Character *mario;
};

#endif // MAINWINDOW_H
