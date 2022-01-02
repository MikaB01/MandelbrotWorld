#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <iostream>
#include <complex>
#include <cmath>

#include "widget.h"

using namespace std;

class Game : public QObject
{
    Q_OBJECT

private:
    static Game *game;
    Game( QObject *parent = 0 );

    Widget *w;

    int maxIteration = 200;
    double middleR = -0.75;
    double middleI = 0;
    double rangeR = 3.5;
    double rangeI = 2;

    void fillScreenTiles();
    int getTileValue(double x, double y);

public:
    static Game *get();

public slots:
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void doubleTileSize();
};

#endif // GAME_H
