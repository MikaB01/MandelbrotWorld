#include "controller.h"

Controller *Controller::controller = nullptr;

Controller::Controller(QObject *parent) : QObject(parent)
{
    g = Game::get();
}

Controller *Controller::get()
{
    if( !controller )
        controller = new Controller();
    return controller;
}
