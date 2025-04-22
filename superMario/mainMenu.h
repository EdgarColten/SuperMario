#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>

#include "levelSelect.h"

class MainMenu : public QDialog
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    void openLevelSelect();
signals:
    void startGame(int level);

private:
    QPushButton *startButton;
};

#endif // MAINMENU_H
