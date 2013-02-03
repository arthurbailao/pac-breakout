#ifndef BREAKOUT_WINDOW_HPP
#define BREAKOUT_WINDOW_HPP

#include "ball.hpp"
#include "paddle.hpp"
#include "brick.hpp"
#include "wall.hpp"
#include "controller.hpp"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

namespace Ui {
class BreakoutWindow;
}

class BreakoutWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BreakoutWindow(QWidget *parent = 0);
    ~BreakoutWindow();
    
private slots:
    void on_pushButtonQuit_clicked();
    void on_pushButtonStartStop_clicked();
    void on_pushButtonNewGame_clicked();

private:
    Ui::BreakoutWindow *ui;
    QGraphicsScene* scene;
    QTimer* timer;
    Controller* controller;

    const qreal sceneWidth, sceneHeight;

    Ball* ball;
    Paddle* playerPaddle;
    Paddle* computerPaddle;
    Wall* topWall;
    Wall* leftWall;
    Wall* bottomWall;
    Wall* rightWall;
    QList<Brick*> bricks;

    void create();
    void createWalls();
    void createPaddles();
    void createBall();
    void createBricks();

    void ballStartPos();
};

#endif // BREAKOUT_WINDOW_HPP
