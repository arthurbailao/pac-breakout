#include "controller.hpp"

Controller::Controller(QObject *parent) :
    QObject(parent),
    lastHit(Human),
    humanScore(0), computerScore(0),
    remainingBalls(6)
{
}

Controller::Players Controller::currentTurn() const
{
    return this->lastHit;
}

void Controller::onHumanPaddleHit()
{
    this->lastHit = Human;
}

void Controller::onComputerPaddleHit()
{
    this->lastHit = Computer;
}

void Controller::onTopBottomWallHit()
{
    this->addScore(1);
}

void Controller::onRightWallHit()
{
    this->computerScore -= 10;
    emit this->computerScoreChanged(QString::number(this->computerScore));

    this->updateRemainingBalls();

    //Passa a vez
    this->lastHit = Human;
}

void Controller::onLeftWallHit()
{
    this->humanScore -= 10;
    emit this->humanScoreChanged(QString::number(this->humanScore));

    this->updateRemainingBalls();

    //Passa a vez
    this->lastHit = Computer;
}

void Controller::onBrickHit()
{
    this->addScore(2);
}

void Controller::addScore(int value)
{
    if(this->lastHit == Human) {
        this->humanScore += value;
        emit this->humanScoreChanged(QString::number(this->humanScore));
    }
    else {
        this->computerScore += value;
        emit this->computerScoreChanged(QString::number(this->computerScore));
    }
}

void Controller::resetGame()
{
    this->humanScore = 0;
    emit this->humanScoreChanged(QString::number(this->humanScore));
    this->computerScore = 0;
    emit this->computerScoreChanged(QString::number(this->computerScore));
    this->remainingBalls = 6;
    emit this->remainingBallsChanged(QString::number(this->remainingBalls));
}

void Controller::updateRemainingBalls()
{
    this->remainingBalls--;
    emit this->remainingBallsChanged(QString::number(this->remainingBalls));
    if(this->remainingBalls == 0) {
        if(this->humanScore > this->computerScore)
            emit this->gameOver(Human);
        else
            emit this->gameOver(Computer);
    }
}
