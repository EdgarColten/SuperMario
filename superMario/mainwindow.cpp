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
}
