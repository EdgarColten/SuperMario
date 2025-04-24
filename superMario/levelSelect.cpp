#include "levelselect.h"

LevelSelect::LevelSelect(QWidget *parent) : QDialog(parent)
{
    setFixedSize(400, 300);
    setWindowTitle("Select Level");

    // Example buttons
    QPushButton *level1Btn = new QPushButton("Level 1-1", this);
    level1Btn->setGeometry(50, 60, 120, 40);

    QPushButton *level2Btn = new QPushButton("Level 1-2", this);
    level2Btn->setGeometry(200, 60, 120, 40);

    connect(level1Btn, &QPushButton::clicked, this, [this]() {
        emit levelChosen(1);
        accept(); // close the dialog
    });

    connect(level2Btn, &QPushButton::clicked, this, [this]() {
        emit levelChosen(2);
        accept();
    });
}
