#include "breakout_window.hpp"
#include "ui_breakout_window.h"

#include "ball.hpp"
#include "paddle.hpp"
#include "wall.hpp"

#include <QDebug>

BreakoutWindow::BreakoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BreakoutWindow),
    scene(new QGraphicsScene(this)),
    timer(new QTimer(this)),
    sceneWidth(400), sceneHeight(300)
{
    ui->setupUi(this);
    ui->view->setScene(this->scene);
    ui->view->setRenderHint(QPainter::Antialiasing);
    ui->view->setMouseTracking(true);

    this->scene->setSceneRect(0,0,this->sceneWidth,this->sceneHeight);
    this->draw();

    connect(this->timer, SIGNAL(timeout()), this->scene, SLOT(advance()));
    this->timer->start(8);
}

BreakoutWindow::~BreakoutWindow()
{
    delete ui;
}

void BreakoutWindow::draw()
{
    this->drawWalls();
    this->drawBall();
    this->drawPaddles();
    this->drawBricks();
}

void BreakoutWindow::drawWalls()
{
    QLineF top(this->scene->sceneRect().topLeft(), this->scene->sceneRect().topRight());
    QLineF left(this->scene->sceneRect().topLeft(), this->scene->sceneRect().bottomLeft());
    QLineF right(this->scene->sceneRect().topRight(), this->scene->sceneRect().bottomRight());
    QLineF bottom(this->scene->sceneRect().bottomLeft(), this->scene->sceneRect().bottomRight());

    this->scene->addItem(new Wall(true, top));
    this->scene->addItem(new Wall(false, left));
    this->scene->addItem(new Wall(false, right));
    this->scene->addItem(new Wall(true, bottom));
}

void BreakoutWindow::drawBall()
{
    this->scene->addItem(new Ball(100, 210));
}

void BreakoutWindow::drawPaddles()
{
    PlayerPaddle* paddle = new PlayerPaddle(this->scene->sceneRect().top(), this->scene->sceneRect().bottom());
    this->scene->installEventFilter(paddle);
    paddle->setPos(1, this->scene->height()/2.0 - paddle->boundingRect().height()/2.0);
    this->scene->addItem(paddle);
}

void BreakoutWindow::drawBricks()
{

}
