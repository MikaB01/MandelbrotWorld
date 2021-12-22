#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <iostream>

#include "widget.h"

class Game : public QObject
{
    Q_OBJECT

private:
    static Game *game;
    Game( QObject *parent = 0 );

    Widget *w;

    void fillScreenTiles();

public:
    static Game *get();

public slots:
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
};

#endif // GAME_H
