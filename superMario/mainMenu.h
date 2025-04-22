#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>

class MainMenu : public QDialog
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);

signals:
    void startGame();

private:
    QPushButton *startButton;
};

#endif // MAINMENU_H
