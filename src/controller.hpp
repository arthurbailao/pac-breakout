#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = 0);

    enum Players {
        Human = 1,
        Computer = 2
    };

    Players currentTurn() const;
    void resetGame();

signals:
    void humanScoreChanged(QString);
    void computerScoreChanged(QString);
    void remainingBallsChanged(QString);
    void gameOver(Controller::Players);
    
public slots:
    void onHumanPaddleHit();
    void onComputerPaddleHit();
    void onTopBottomWallHit();
    void onRightWallHit();
    void onLeftWallHit();
    void onBrickHit();

private:
    Players lastHit;
    int humanScore, computerScore;
    int remainingBalls;

    void addScore(int value);
    void updateRemainingBalls();
    
};

#endif // CONTROLLER_HPP
