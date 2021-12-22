#include "game.h"

Game *Game::game = nullptr;

Game::Game(QObject *parent) : QObject(parent)
{
    w = Widget::get();

    connect(w, SIGNAL(upPressed()), this, SLOT(moveUp()));
    connect(w, SIGNAL(downPressed()), this, SLOT(moveDown()));
    connect(w, SIGNAL(rightPressed()), this, SLOT(moveRight()));
    connect(w, SIGNAL(leftPressed()), this, SLOT(moveLeft()));

    fillScreenTiles();

    w->setWindowState(Qt::WindowFullScreen);
    w->show();
}

void Game::fillScreenTiles()
{
    for(int y = 0; y < w->getScreenTileSize().height() + 1; y++)
        for(int x = 0; x < w->getScreenTileSize().width() + 1; x++) {
            w->screenTiles.append(y);
        }
}

Game *Game::get()
{
    if( !game )
        game = new Game();
    return game;
}

void Game::moveUp()
{
    std::cout << "Up" << std::endl;
    w->screenTiles.clear();
    for(int y = 0; y < w->getScreenTileSize().height() + 1; y++)
        for(int x = 0; x < w->getScreenTileSize().width() + 1; x++) {
            w->screenTiles.append(x);
        }
    w->repaint();
}

void Game::moveDown()
{
    std::cout << "Down" << std::endl;
}

void Game::moveRight()
{
    std::cout << "Right" << std::endl;
}

void Game::moveLeft()
{
    std::cout << "Left" << std::endl;
}

