#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "Block.h"
#include "ItemBlock.h"
#include "Character.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createLevel();
    QList<Block*> blocks; // All blocks that form the level
    Character *mario;
};

#endif // MAINWINDOW_H
