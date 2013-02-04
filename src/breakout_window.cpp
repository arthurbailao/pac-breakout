#include "breakout_window.hpp"
#include "ui_breakout_window.h"

#include <QDebug>
#include <QMessageBox>

BreakoutWindow::BreakoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BreakoutWindow),
    scene(new QGraphicsScene(this)),
    timer(new QTimer(this)),
    controller(new Controller(this)),
    sceneWidth(400), sceneHeight(300),
    ball(NULL),
    humanPaddle(NULL), computerPaddle(NULL),
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

    connect(this->controller, SIGNAL(humanScoreChanged(QString)), ui->labelPlayerPoints, SLOT(setText(QString)));
    connect(this->controller, SIGNAL(computerScoreChanged(QString)), ui->labelComputerPoints, SLOT(setText(QString)));
    connect(this->controller, SIGNAL(remainingBallsChanged(QString)), ui->labelNumberOfBalls, SLOT(setText(QString)));
    connect(this->controller, SIGNAL(gameOver(Controller::Players)), this, SLOT(onGameOver(Controller::Players)));
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
    this->humanPaddle = new HumanPaddle(this->scene->sceneRect().top(), this->scene->sceneRect().bottom());
    connect(this->humanPaddle, SIGNAL(posChanged(QString)), ui->labelPlayerPaddlePos, SLOT(setText(QString)));
    this->humanPaddle->setPos(5.0, this->scene->height()/2.0 - this->humanPaddle->boundingRect().height()/2.0);
    this->scene->addItem(this->humanPaddle);
    ui->labelPlayerPaddlePos->setText(QString::number((int)this->humanPaddle->y()));

    this->computerPaddle = new ComputerPaddle(this->scene->sceneRect().top(), this->scene->sceneRect().bottom());
    connect(this->computerPaddle, SIGNAL(posChanged(QString)), ui->labelComputerPaddlePos, SLOT(setText(QString)));
    this->computerPaddle->setPos(this->scene->width() - 20.0, this->scene->height()/2.0 - this->computerPaddle->boundingRect().height()/2.0);
    this->scene->addItem(this->computerPaddle);
    ui->labelComputerPaddlePos->setText(QString::number((int)this->computerPaddle->y()));

}

void BreakoutWindow::createBall()
{
    this->ball = new Ball(0, 0);
    connect(ball, SIGNAL(posChanged(QString)), ui->labelBallPosition, SLOT(setText(QString)));
    connect(ui->ballSpeedSlider, SIGNAL(valueChanged(int)), ball, SLOT(setBallSpeed(int)));
    connect(this->ball, SIGNAL(topBottomWallHit()), this->controller, SLOT(onTopBottomWallHit()));

    connect(this->ball, SIGNAL(leftWallHit()), this->controller, SLOT(onLeftWallHit()));
    connect(this->ball, SIGNAL(leftWallHit()), this, SLOT(ballStartPos()));
    connect(this->ball, SIGNAL(rightWallHit()), this->controller, SLOT(onRightWallHit()));
    connect(this->ball, SIGNAL(rightWallHit()), this, SLOT(ballStartPos()));

    connect(this->ball, SIGNAL(computerPaddleHit()), this->controller, SLOT(onComputerPaddleHit()));
    connect(this->ball, SIGNAL(humanPaddleHit()), this->controller, SLOT(onHumanPaddleHit()));

    this->ballStartPos();
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
            connect(brick, SIGNAL(imDestroyed()), this->controller, SLOT(onBrickHit()));
            this->scene->addItem(brick);
        }
    }
    this->controller->setTotalBricks(this->bricks.length());
}

void BreakoutWindow::ballStartPos()
{
    QPointF startPoint;
    if(this->controller->currentTurn() == Controller::Human) {
        startPoint = QPointF(20.0, this->scene->height()/2.0);
        this->ball->setDirection(startPoint, startPoint + QPointF(1.0, 0));
    }
    else {
        startPoint = QPointF(this->scene->width() - 30.0, this->scene->height()/2.0);
        this->ball->setDirection(startPoint, startPoint + QPointF(-1.0, 0));
    }
    if(this->timer->isActive())
        this->on_pushButtonStartStop_clicked();
    this->ball->setPos(startPoint);
    this->ball->enableCollisions();
}


void BreakoutWindow::on_pushButtonQuit_clicked()
{
    this->close();
}

void BreakoutWindow::on_pushButtonStartStop_clicked()
{
    if(this->timer->isActive()) {
        this->scene->removeEventFilter(this->humanPaddle);
        ui->pushButtonStartStop->setText("Iniciar");
        this->timer->stop();
    }
    else {
        this->scene->installEventFilter(this->humanPaddle);
        ui->pushButtonStartStop->setText("Pausar");
        this->timer->start(10);
        this->ball->setBallSpeed(ui->ballSpeedSlider->value());
    }
}

void BreakoutWindow::on_pushButtonNewGame_clicked()
{
    if(this->timer->isActive())
        this->on_pushButtonStartStop_clicked();

    QMessageBox::StandardButton answer = QMessageBox::question(this, "Novo Jogo", "Deseja abandonar o jogo?",
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if(answer == QMessageBox::Yes) {
        this->ballStartPos();
        Q_FOREACH(Brick* brick, this->bricks) {
            brick->build();
        }
        this->controller->resetGame();
    }
    else {
        this->on_pushButtonStartStop_clicked();
    }
}

void BreakoutWindow::onGameOver(Controller::Players player)
{
    if(this->timer->isActive())
        this->on_pushButtonStartStop_clicked();

    QString message;
    if(player == Controller::Human)
        message = QString::fromUtf8("Parabéns, você venceu!");
    else
        message = QString::fromUtf8("Você foi derrotado.");

    QMessageBox::StandardButton answer = QMessageBox::question(this, "Game Over", message + QString(" Deseja jogar novamente?"),
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if(answer == QMessageBox::Yes) {
        this->ballStartPos();
        Q_FOREACH(Brick* brick, this->bricks) {
            brick->build();
        }
        this->controller->resetGame();
    }
    else {
        this->on_pushButtonQuit_clicked();
    }
}

