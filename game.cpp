#include "game.h"

Game *Game::game = nullptr;

Game::Game(QObject *parent) : QObject(parent)
{
    w = Widget::get();

    connect(w, SIGNAL(upPressed()), this, SLOT(moveUp()));
    connect(w, SIGNAL(downPressed()), this, SLOT(moveDown()));
    connect(w, SIGNAL(rightPressed()), this, SLOT(moveRight()));
    connect(w, SIGNAL(leftPressed()), this, SLOT(moveLeft()));
    connect(w, SIGNAL(pPressed()), this, SLOT(doubleTileSize()));

    fillScreenTiles();

    w->setWindowState(Qt::WindowFullScreen);
    w->show();
}

void Game::fillScreenTiles()
{
    w->screenTiles.clear();
    for(double x = 0; x < w->getScreenTileSize().width()+1; x++)
        for(double y = 0; y < w->getScreenTileSize().height()+1; y ++) {
            double xPercentage = x / double(w->getScreenTileSize().width());
            double yPercentage = y / double(w->getScreenTileSize().height());

            double cReal = xPercentage * rangeR + middleR - rangeR / 2;
            double cImag = yPercentage * rangeI + middleI - rangeI / 2;

            w->screenTiles.append(getTileValue(cReal, cImag));
        }
}

int Game::getTileValue(double cReal, double cImag)
{
    double zReal = 0;
    double zImag = 0;

    int iteration = 0;
    while(iteration < maxIteration && (zReal * zReal + zImag * zImag) <= 4) {
        double tmp = zReal * zReal - zImag * zImag + cReal;
        zImag = 2 * zReal * zImag + cImag;
        zReal = tmp;
        iteration++;
    }
    if(iteration >= maxIteration -1) {
        return 0;
    }
    return 1;
}

Game *Game::get()
{
    if( !game )
        game = new Game();
    return game;
}

void Game::moveUp()
{
    w->moveUp();
}

void Game::moveDown()
{
    w->moveDown();
}

void Game::moveRight()
{
    w->moveRight();
}

void Game::moveLeft()
{
    w->moveLeft();
}

void Game::doubleTileSize()
{
    if(w->getTileSize() <= 1) {
        w->setTileSize(64);
    } else {
        w->setTileSize(w->getTileSize()/2);
    }
    fillScreenTiles();
    w->repaint();
}

