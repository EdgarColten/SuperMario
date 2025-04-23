#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QPushButton>


class LevelSelect : public QDialog
{
    Q_OBJECT

public:
    explicit LevelSelect(QWidget *parent = nullptr);

signals:
    void levelChosen(int level);
};

#endif // LEVELSELECT_H
