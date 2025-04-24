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

    backgroundImage = new QLabel(this);
    QPixmap backgroundPix(":/images/background.png");
    backgroundImage->setPixmap(backgroundPix.scaled(1074,562, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    backgroundImage->setFixedSize(1074, 562);
    backgroundImage->move(0, 0);
    backgroundImage->lower();
    backgroundImage->show();
    mario->setBackground(backgroundImage);

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

void MainWindow::createLevel2()
{

    backgroundImage = new QLabel(this);
    QPixmap backgroundPix(":/images/background1.jpg");
    backgroundImage->setPixmap(backgroundPix.scaled(1074,562, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    backgroundImage->setFixedSize(1074, 562);
    backgroundImage->move(0, 0);
    backgroundImage->lower();
    backgroundImage->show();
    mario->setBackground(backgroundImage);

        // Platform 2: a row of blocks at y = 500 (ground level)
    for (int i = 0; i < 90; ++i) {
        Block *groundBlock = new Block(":/images/block.png", this);
        groundBlock->move(i * 55 + 20 + (i *5), 500);
        groundBlock->show();
        blocks.append(groundBlock);

    }

    for (int i = 35; i < 40; ++i) {
        Block *groundBlock = new Block(":/images/block2.png", this);
        groundBlock->move(i * 55 + 20 + (i *5), 450);
        groundBlock->show();
        blocks.append(groundBlock);
    }
    for (int i = 36; i < 40; ++i) {
        Block *groundBlock = new Block(":/images/block2.png", this);
        groundBlock->move(i * 55 + 20 + (i *5), 400);
        groundBlock->show();
        blocks.append(groundBlock);
    }
    for (int i = 37; i < 40; ++i) {
        Block *groundBlock = new Block(":/images/block2.png", this);
        groundBlock->move(i * 55 + 20 + (i *5), 350);
        groundBlock->show();
        blocks.append(groundBlock);
    }

    for (int i = 46; i < 49; ++i) {
        Block *groundBlock = new Block(":/images/block2.png", this);
        groundBlock->move(i * 55 + 20 + (i *5), 350);
        groundBlock->show();
        blocks.append(groundBlock);
    }
    for (int i = 46; i < 50; ++i) {
        Block *groundBlock = new Block(":/images/block2.png", this);
        groundBlock->move(i * 55 + 20 + (i *5), 400);
        groundBlock->show();
        blocks.append(groundBlock);
    }
    for (int i = 46; i < 51; ++i) {
        Block *groundBlock = new Block(":/images/block2.png", this);
        groundBlock->move(i * 55 + 20 + (i *5), 450);
        groundBlock->show();
        blocks.append(groundBlock);
    }

    for (int i = 0; i < 5; ++i) {
        Block *groundBlock = new Block(":/images/block3.png", this);
        groundBlock->move(i * 55 + 20 + (i *5)+400, 340);
        groundBlock->show();
        blocks.append(groundBlock);
    }
    ItemBlock *itemBlock = new ItemBlock(":/images/question_block.png", ":/images/mushroom.png", this);
    // Place it between platforms (for example at y = 340)
    itemBlock->move(550, 180);
    itemBlock->show();
    blocks.append(itemBlock);





    Pipe *pipe = new Pipe(":/images/mediumPipe.png", this);
    pipe->move(900, 400);
    pipe->show();
    pipes.append(pipe);

    Pipe *pipe1 = new Pipe(":/images/mediumPipe.png", this);
    pipe1->move(1200, 400);
    pipe1->show();
    pipes.append(pipe1);

    Pipe *pipe2 = new Pipe(":/images/mediumPipe.png", this);
    pipe2->move(3500, 400);
    pipe2->show();
    pipes.append(pipe2);

    Pipe *pipe3 = new Pipe(":/images/mediumPipe.png", this);
    pipe3->move(4000, 400);
    pipe3->show();
    pipes.append(pipe3);

    Pipe *pipe4 = new Pipe(":/images/mediumPipe.png", this);
    pipe4->move(4500, 400);
    pipe4->show();
    pipes.append(pipe4);

    ItemBlock *itemBlock1 = new ItemBlock(":/images/question_block.png", ":/images/mushroom.png", this);
    // Place it between platforms (for example at y = 340)
    itemBlock1->move(4250, 260);
    itemBlock1->show();
    blocks.append(itemBlock1);


    Flag *flagBlock = new Flag(":/images/flag.png", this);
    flagBlock->move(5000, 110);
    flagBlock->show();
    flag.append(flagBlock);

    Goomba *goomba = new Goomba(":/images/Anigoomba.gif", this);
    goomba->move(700, 445);
    goomba->show();
    goomba->setPipes(pipes);
    goombas.append(goomba);

    Goomba *goomba1 = new Goomba(":/images/Anigoomba.gif", this);
    goomba1->move(750, 445);
    goomba1->show();
    goomba1->setPipes(pipes);
    goombas.append(goomba1);


    Koopa *koopa2 = new Koopa(":/images/Anikoopa.gif", this);
    koopa2->move(1700, 425);
    koopa2->setPipes(pipes);
    koopa2->setBlocks(blocks);
    koopa2->show();
    koopas.append(koopa2);

    Koopa *koopa = new Koopa(":/images/Anikoopa.gif", this);
    koopa->move(4100, 438);
    koopa->setPipes(pipes);
    koopa->show();
    koopas.append(koopa);

    for(int i = 40; i<46; i++){
        Goomba *goomba = new Goomba(":/images/Anigoomba.gif", this);
        goomba->move(i * 55 + 20 + (i *5), 445);
        goomba->show();
        goomba->setPipes(pipes);
        goomba->setBlocks(blocks);
        goombas.append(goomba);
    }

    //    int playerLives = 3;
    QString currentLevelName = "1-2";
    connect(flagBlock, &Flag::levelCompleted, this, [this, flagBlock, currentLevelName]() { mario->freeze();flagBlock->levelCompletedHandler(currentLevelName);});
    connect(flagBlock, &Flag::backToMainMenu, this, &MainWindow::showMainMenu);

    castle = new QLabel(this);
    QPixmap castlePix(":/images/castle.png");
    castle->setPixmap(castlePix.scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    castle->setFixedSize(200, 300);
    castle->move(5150, 240);
    castle->lower();
    castle->show();

}
void MainWindow::startGame(int level)
{
    setFixedSize(800, 600);
    if(level == 1)
        createLevel();
    else if(level == 2)
        createLevel2();
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


