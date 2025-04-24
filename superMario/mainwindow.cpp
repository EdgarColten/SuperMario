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

    // --- Ground Level ---
    for (int i = 0; i < 70; ++i) {
        Block *groundBlock = new Block(":/images/block.png", this);
        groundBlock->move(i * 50, 500);
        groundBlock->show();
        blocks.append(groundBlock);
    }

    // --- Floating Platform 1 ---
    for (int i = 0; i < 5; ++i) {
        Block *floatingBlock1 = new Block(":/images/block2.png", this);
        floatingBlock1->move(300 + i * 55, 350); // Higher up
        floatingBlock1->show();
        blocks.append(floatingBlock1);
    }

    Pipe *pipe = new Pipe(":/images/mediumPipe.png", this);
    pipe->move(900, 400);
    pipe->show();
    pipes.append(pipe);

    Pipe *pipe1 = new Pipe(":/images/mediumPipe.png", this);
    pipe1->move(1200, 400);
    pipe1->show();
    pipes.append(pipe1);


    Pipe *pipe2 = new Pipe(":/images/mediumPipe.png", this);
    pipe2->move(2100, 400);
    pipe2->show();
    pipes.append(pipe2);



    Pipe *pipe4 = new Pipe(":/images/mediumPipe.png", this);
    pipe4->move(1650, 400);
    pipe4->show();
    pipes.append(pipe4);

    // --- Floating Platform 2 ---
    for (int i = 0; i < 3; ++i) {
        Block *floatingBlock1 = new Block(":/images/block3.png", this);
        floatingBlock1->move(1400 + i * 55, 250); // Higher up
        floatingBlock1->show();
        blocks.append(floatingBlock1);
    }

    // --- Floating Platform 2 ---
    for (int i = 0; i < 3; ++i) {
        Block *floatingBlock1 = new Block(":/images/block3.png", this);
        floatingBlock1->move(1800 + i * 55, 250); // Higher up
        floatingBlock1->show();
        blocks.append(floatingBlock1);
    }

    // --- Question Block with a Mushroom ---
    ItemBlock *mushroomBlock = new ItemBlock(":/images/question_block.png", ":/images/mushroom.png", this);
    mushroomBlock->move(400, 200); // Above the first floating platform
    mushroomBlock->show();
    blocks.append(mushroomBlock);



    // --- Goomba Placement ---
    Goomba *goomba1 = new Goomba(":/images/Anigoomba.gif", this);
    goomba1->move(1100, 443); // On the first floating platform (adjust y based on Goomba height)
    goomba1->show();
    goomba1->setPipes(pipes);
    goombas.append(goomba1);

    // --- Goomba Placement ---
    Goomba *goomba2 = new Goomba(":/images/Anigoomba.gif", this);
    goomba2->move(2200, 443); // On the first floating platform (adjust y based on Goomba height)
    goomba2->show();
    goomba2->setPipes(pipes);
    goombas.append(goomba2);

    // --- Goomba Placement ---
    Goomba *goomba3 = new Goomba(":/images/Anigoomba.gif", this);
    goomba3->move(1500, 443); // On the first floating platform (adjust y based on Goomba height)
    goomba3->show();
    goomba3->setPipes(pipes);
    goombas.append(goomba3);

    // --- Goomba Placement ---
    Goomba *goomba4 = new Goomba(":/images/Anigoomba.gif", this);
    goomba4->move(2000, 443); // On the first floating platform (adjust y based on Goomba height)
    goomba4->show();
    goomba4->setPipes(pipes);
    goombas.append(goomba4);


    // --- Koopa Placement ---
    Koopa *koopa1 = new Koopa(":/images/Anikoopa.gif", this);
    koopa1->move(800, 438); // Starting area patrol
    koopa1->setPipes(pipes);
    koopa1->show();
    koopas.append(koopa1);


    // --- Flag and Castle (End of Level) ---
    Flag *flagBlock = new Flag(":/images/flag.png", this);
    flagBlock->move(2650, 110); // Further to the right
    flagBlock->show();
    flag.append(flagBlock);



    castle = new QLabel(this);
    QPixmap castlePix(":/images/castle.png");
    castle->setPixmap(castlePix.scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    castle->setFixedSize(200, 300);
    castle->move(2800, 230); // Closer to the flag
    castle->lower();
    castle->show();

    QString currentLevelName = "1-1"; // A new level name
    connect(flagBlock, &Flag::levelCompleted, this, [this, flagBlock, currentLevelName]() { mario->freeze(); flagBlock->levelCompletedHandler(currentLevelName); });
    connect(flagBlock, &Flag::backToMainMenu, this, &MainWindow::showMainMenu);
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
