#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
/*    setFixedSize(800, 600);
    createLevel();

    // Create Mario; start him high so he falls onto a block
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
*/
    MainMenu *menu = new MainMenu(this);
    connect(menu, &MainMenu::startGame, this, &MainWindow::startGame);
    menu->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::showMainMenu()
{
    if (mario) {
            mario->hide();
            delete mario;
            mario = nullptr;
        }

        qDeleteAll(blocks);
        blocks.clear();
        qDeleteAll(mushrooms);
        mushrooms.clear();
        qDeleteAll(goombas);
        goombas.clear();
        qDeleteAll(koopas);
        koopas.clear();
        qDeleteAll(pipes);
        pipes.clear();
        qDeleteAll(flag);
        flag.clear();

        if (castle) {
            castle->hide();
            delete castle;
            castle = nullptr;
        }

        // Show menu again
        MainMenu *menu = new MainMenu(this);
        connect(menu, &MainMenu::startGame, this, [=]() {
            menu->close();
            startGame(1);
        });
        menu->exec();
}

void MainWindow::createLevel()
{

    // Platform 2: a row of blocks at y = 500 (ground level)
    for (int i = 0; i < 30; ++i) {
        Block *groundBlock = new Block(":/images/block.png", this);
        groundBlock->move(i * 55 + 20 + (i *5), 500);
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
    connect(flagBlock, &Flag::backToMainMenu, this, &MainWindow::showMainMenu);

    castle = new QLabel(this);
    QPixmap castlePix(":/images/castle.png");
    castle->setPixmap(castlePix.scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    castle->setFixedSize(200, 300);
    castle->move(550, 200);
    castle->lower();
    castle->show();

}

void MainWindow::startGame(int level)
{
    setFixedSize(800, 600);
    if(level == 1)
        createLevel();
    else if(level == 2)
        return;
    else if(level == 3)
        return;

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
}

void MainWindow::startNextLevel()
{
    mario->unfreeze();
    mario->move(100,0);
}
