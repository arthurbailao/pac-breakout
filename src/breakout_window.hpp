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

//Janela principal do jogo.
class BreakoutWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BreakoutWindow(QWidget *parent = 0);
    ~BreakoutWindow();
    
private slots:
    //Slots dos botões de controle
    void on_pushButtonQuit_clicked();
    void on_pushButtonStartStop_clicked();
    void on_pushButtonNewGame_clicked();

    //Slot que posiciona a bola em sua posição inicial, seja para o jogador, seja para o computador.
    void ballStartPos();
    //Slot que é chamado quando o jogo termina.
    void onGameOver(Controller::Players player);

private:
    Ui::BreakoutWindow *ui;
    QGraphicsScene* scene;
    QTimer* timer;
    Controller* controller;

    const qreal sceneWidth, sceneHeight;

    Ball* ball;
    Paddle* humanPaddle;
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
};

#endif // BREAKOUT_WINDOW_HPP
