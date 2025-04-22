#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);

    createLevel2();

    mario = new Character(this);
    mario->move(100, 0);
    mario->setBlocks(blocks);
    mario->setMush(mushrooms);
    mario->setGoombas(goombas);
    mario->setKoopas(koopas);
    mario->setPipes(pipes);
    mario->setFlag(flag);
    mario->setCastle(castle);

    mario->show();
    // Create Mario; start him high so he falls onto a block
}

MainWindow::~MainWindow()
{
}

void MainWindow::createLevel()
{


    // Platform 2: a row of blocks at y = 500 (ground level)
    for (int i = 0; i < 30; ++i) {
        Block *groundBlock = new Block(":/images/block.png", this);
        groundBlock->move(i * 55 + 20, 500);
        groundBlock->show();
        blocks.append(groundBlock);
    }

    ItemBlock *itemBlock = new ItemBlock(":/images/question_block.png", ":/images/mushroom.png", this);
    // Place it between platforms (for example at y = 340)
    itemBlock->move(200, 340);
    itemBlock->show();
    blocks.append(itemBlock);

    Block *groundBlock = new Block(":/images/block1.png", this);
    groundBlock->move( 55 + 20, 300);
    groundBlock->show();
    blocks.append(groundBlock);

    Koopa *koopa = new Koopa(":/images/Anikoopa.gif", this);
    koopa->move(450, 438);
    koopa->show();
    koopas.append(koopa);

    Goomba *goomba = new Goomba(":/images/Anigoomba.gif", this);
    goomba->move(370, 445);
    goomba->show();
    goombas.append(goomba);

    Pipe *pipe = new Pipe(":/images/mediumPipe.png", this);
    pipe->move(500, 400);
    pipe->show();
    pipes.append(pipe);

    Flag *flagBlock = new Flag(":/images/flag.png", this);
    flagBlock->move(800, 110);
    flagBlock->show();
    flag.append(flagBlock);
//    int playerLives = 3;
    QString currentLevelName = "1-2";
    connect(flagBlock, &Flag::levelCompleted, this, [this, flagBlock, currentLevelName]() { mario->freeze();flagBlock->levelCompletedHandler(currentLevelName);});
    connect(flagBlock, &Flag::transitionToNextLevel, this, &MainWindow::startNextLevel);

    castle = new QLabel(this);
    QPixmap castlePix(":/images/castle.png");
    castle->setPixmap(castlePix.scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    castle->setFixedSize(200, 300);
    castle->move(850, 200);
    castle->lower();
    castle->show();

}

void MainWindow::createLevel2()
{
    for (int i = 0; i < 80; ++i) {
        Block *groundBlock = new Block(":/images/block.png", this);
        groundBlock->move(i * 55 + 20, 500);
        groundBlock->show();
        blocks.append(groundBlock);
    }

    ItemBlock *itemBlock = new ItemBlock(":/images/question_block.png", ":/images/mushroom.png", this);
    // Place it between platforms (for example at y = 340)
    itemBlock->move(200, 340);
    itemBlock->show();
    blocks.append(itemBlock);

    for (int i = 0; i < 4; ++i) {
        Block *groundBlock = new Block(":/images/block.png", this);
        groundBlock->move(i * 55 + 300, 500);
        groundBlock->show();
        blocks.append(groundBlock);
    }

    Koopa *koopa = new Koopa(":/images/Anikoopa.gif", this);
    koopa->move(450, 438);
    koopa->show();
    koopas.append(koopa);

    Koopa *koopa1 = new Koopa(":/images/Anikoopa.gif", this);
    koopa1->move(800, 438);
    koopa1->show();
    koopas.append(koopa1);

    Goomba *goomba = new Goomba(":/images/Anigoomba.gif", this);
    goomba->move(370, 445);
    goomba->show();
    goombas.append(goomba);

    Pipe *pipe = new Pipe(":/images/mediumPipe.png", this);
    pipe->move(500, 400);
    pipe->show();
    pipes.append(pipe);

    Flag *flagBlock = new Flag(":/images/flag.png", this);
    flagBlock->move(4000, 110);
    flagBlock->show();
    flag.append(flagBlock);
//    int playerLives = 3;
    QString currentLevelName = "1-2";
    connect(flagBlock, &Flag::levelCompleted, this, [this, flagBlock, currentLevelName]() { mario->freeze();flagBlock->levelCompletedHandler(currentLevelName);});
    connect(flagBlock, &Flag::transitionToNextLevel, this, &MainWindow::startNextLevel);

    castle = new QLabel(this);
    QPixmap castlePix(":/images/castle.png");
    castle->setPixmap(castlePix.scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    castle->setFixedSize(200, 300);
    castle->move(4200, 250);
    castle->lower();
    castle->show();
}

void MainWindow::createLevel3()
{

}

void MainWindow::startNextLevel()
{
    mario->unfreeze();
    mario->move(100,0);
}

void MainWindow::onStartClicked()
{
    QList<QWidget*> widgets = this->findChildren<QWidget*>();
    for (QWidget* wid: widgets){
        if (wid != mario)
            wid->deleteLater();
    }
    createLevel();

}

void MainWindow::onExitClicked()
{
    QApplication::quit();
}

void MainWindow::mainMenu()
{
    QList<QWidget*> widgets = this->findChildren<QWidget*>();
    for (QWidget* wid: widgets){
        wid->deleteLater();
    }

    QLabel *marioLogo = new QLabel(this);
    QPixmap marioLogoPixmap(":/images/marioLogo.png");
    marioLogo->setPixmap(marioLogoPixmap);
    marioLogo->setGeometry(200,80,400,100);
    marioLogo->setAlignment(Qt::AlignCenter);
    marioLogo->show();

    QPushButton *level1B = new QPushButton("Start Level 1", this);
    level1B->setGeometry(300, 200, 200, 50);
    connect(level1B, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    level1B->show();

    QPushButton *exitButton = new QPushButton("Exit Game", this);
    exitButton->setGeometry(300, 410, 200, 50);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);
    exitButton->show();
}
