#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);
    createLevel();

    // Create Mario; start him high so he falls onto a block
    mario = new Character(this);
    mario->move(100, 0);
    mario->setBlocks(blocks);
    mario->setGoombas(goombas);
    mario->setKoopas(koopas);
    mario->setPipes(pipes);
    mario->show();

}

MainWindow::~MainWindow()
{
}

void MainWindow::createLevel()
{
    // Platform 2: a row of blocks at y = 500 (ground level)
    for (int i = 0; i < 10; ++i) {
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
    pipe->move(300, 400);
    pipe->show();
    pipes.append(pipe);
}
