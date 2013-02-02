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
    ui->view->installEventFilter(this->scene);
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
    QPen pen(Qt::blue);

    QLineF top(this->scene->sceneRect().topLeft(), this->scene->sceneRect().topRight());
    QLineF left(this->scene->sceneRect().topLeft(), this->scene->sceneRect().bottomLeft());
    QLineF right(this->scene->sceneRect().topRight(), this->scene->sceneRect().bottomRight());
    QLineF bottom(this->scene->sceneRect().bottomLeft(), this->scene->sceneRect().bottomRight());

//    this->scene->addLine(top, pen);
//    this->scene->addLine(left, pen);
//    this->scene->addLine(right, pen);
//    this->scene->addLine(bottom, pen);

    this->scene->addItem(new Ball(100, 210));
    PlayerPaddle* paddle = new PlayerPaddle;
    this->scene->installEventFilter(paddle);
    this->scene->addItem(paddle);
    this->scene->addItem(new Wall(top));
    this->scene->addItem(new Wall(left));
    this->scene->addItem(new Wall(right));
    this->scene->addItem(new Wall(bottom));
}
