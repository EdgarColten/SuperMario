/*#include "levelselect.h"

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
*/
#include "levelselect.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QPixmap>

LevelSelect::LevelSelect(QWidget *parent) : QDialog(parent)
{
    setFixedSize(400, 300);
    setWindowTitle("Select Level");

    // Set background image or color
    setStyleSheet(R"(
        LevelSelect {
            background-color: #330000;
            background-image: url(:/images/marioBG.png); /* optional background image */
            background-repeat: no-repeat;
            background-position: center;
        }
        QPushButton {
            background-color: #aa0000;
            color: white;
            font-family: 'Courier New', monospace;
            font-size: 16px;
            border: 2px solid #ff6666;
            border-radius: 8px;
            padding: 8px;
        }
        QPushButton:hover {
            background-color: #cc3333;
        }
        QPushButton:pressed {
            background-color: #990000;
        }
    )");

    // Create layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("Choose Your Level", this);
    title->setStyleSheet("color: Black; font-size: 20px; font-weight: bold;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    mainLayout->addStretch(1);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *level1Btn = new QPushButton("Level 1-1", this);
    QPushButton *level2Btn = new QPushButton("Level 1-2", this);
    buttonLayout->addWidget(level1Btn);
    buttonLayout->addWidget(level2Btn);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);

    // Connect buttons
    connect(level1Btn, &QPushButton::clicked, this, [this]() {
        emit levelChosen(1);
        accept();
    });

    connect(level2Btn, &QPushButton::clicked, this, [this]() {
        emit levelChosen(2);
        accept();
    });
}
