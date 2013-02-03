#include "breakout_window.hpp"
#include "ui_breakout_window.h"

#include <QDebug>

BreakoutWindow::BreakoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BreakoutWindow),
    scene(new QGraphicsScene(this)),
    timer(new QTimer(this)),
    controller(new Controller(this)),
    sceneWidth(400), sceneHeight(300),
    ball(NULL),
    playerPaddle(NULL), computerPaddle(NULL),
    topWall(NULL), leftWall(NULL), bottomWall(NULL),rightWall(NULL),
    bricks(QList<Brick*>())
{
    ui->setupUi(this);
    ui->view->setScene(this->scene);
    ui->view->setRenderHint(QPainter::Antialiasing);
    ui->view->setMouseTracking(true);

    this->scene->setSceneRect(0,0,this->sceneWidth,this->sceneHeight);
    this->create();

    connect(this->timer, SIGNAL(timeout()), this->scene, SLOT(advance()));
//    this->timer->start(10);
}

BreakoutWindow::~BreakoutWindow()
{
    delete ui;
}

void BreakoutWindow::create()
{
    this->createWalls();
    this->createPaddles();
    this->createBall();
    this->createBricks();
}


void BreakoutWindow::createWalls()
{
    QLineF top(this->scene->sceneRect().topLeft(), this->scene->sceneRect().topRight());
    QLineF left(this->scene->sceneRect().topLeft(), this->scene->sceneRect().bottomLeft());
    QLineF right(this->scene->sceneRect().topRight(), this->scene->sceneRect().bottomRight());
    QLineF bottom(this->scene->sceneRect().bottomLeft(), this->scene->sceneRect().bottomRight());

    this->topWall = new Wall(true, top);
    this->leftWall = new Wall(false, left);
    this->bottomWall = new Wall(true, bottom);
    this->rightWall = new Wall(false, right);

    this->scene->addItem(this->topWall);
    this->scene->addItem(this->leftWall);
    this->scene->addItem(this->bottomWall);
    this->scene->addItem(this->rightWall);
}

void BreakoutWindow::createPaddles()
{
    this->playerPaddle = new PlayerPaddle(this->scene->sceneRect().top(), this->scene->sceneRect().bottom());
    connect(this->playerPaddle, SIGNAL(posChanged(QString)), ui->labelPlayerPaddlePos, SLOT(setText(QString)));
    this->scene->installEventFilter(this->playerPaddle);
    this->playerPaddle->setPos(5.0, this->scene->height()/2.0 - this->playerPaddle->boundingRect().height()/2.0);
    this->scene->addItem(this->playerPaddle);
}

void BreakoutWindow::createBall()
{
    this->ball = new Ball(0, 0);
    this->ballStartPos();
    connect(ball, SIGNAL(posChanged(QString)), ui->labelBallPosition, SLOT(setText(QString)));
    connect(ui->ballSpeedSlider, SIGNAL(valueChanged(int)), ball, SLOT(setBallSpeed(int)));
    this->scene->addItem(ball);
}

void BreakoutWindow::createBricks()
{
    const int cols = 9;
    const int rows = 8;
    const qreal offSet = 4.0;

    for(int i = 0; i < cols; ++i) {
        for(int j = 0; j < rows; ++j) {
            Brick* brick = new Brick(0, 0);
            const qreal x0 = (this->scene->width() / 2.0) - (cols * brick->boundingRect().width() + ((cols - 1) * offSet))/2.0;
            const qreal y0 = (this->scene->height() / 2.0) - (rows * brick->boundingRect().height() + ((rows - 1) * offSet))/2.0;
            brick->setPos(i * (brick->boundingRect().width() + offSet) + x0, j * (brick->boundingRect().height() + offSet) + y0);
            this->bricks << brick;
            this->scene->addItem(brick);
        }
    }
}

void BreakoutWindow::ballStartPos()
{
    if(this->controller->currentTurn() == Controller::Human) {
        QPointF startPoint = this->playerPaddle->pos() + QPointF(20.0, this->playerPaddle->boundingRect().height()/2.0);
        this->ball->setPos(startPoint);
        this->ball->setDirection(startPoint, startPoint + QPointF(1.0, 0));
    }
}


void BreakoutWindow::on_pushButtonQuit_clicked()
{
    this->close();
}

void BreakoutWindow::on_pushButtonStartStop_clicked()
{
    if(this->timer->isActive()) {
        ui->pushButtonStartStop->setText("Iniciar");
        this->timer->stop();
    }
    else {
        ui->pushButtonStartStop->setText("Pausar");
        this->timer->start(10);
        this->ball->setBallSpeed(ui->ballSpeedSlider->value());
    }
}

void BreakoutWindow::on_pushButtonNewGame_clicked()
{

}

