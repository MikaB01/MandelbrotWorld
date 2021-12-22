#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "game.h"

class Controller : public QObject
{
    Q_OBJECT

private:
    static Controller *controller;
    Controller( QObject *parent = 0 );

    Game *g;

public:
    static Controller *get();

public slots:
};

#endif // CONTROLLER_H
