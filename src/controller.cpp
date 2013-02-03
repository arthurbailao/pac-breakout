#include "controller.hpp"

Controller::Controller(QObject *parent) :
    QObject(parent),
    turn(Human),
    lastHit(Human)
{
}
