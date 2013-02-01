#include "breakout_window.hpp"
#include "ui_breakout_window.h"

#include "ball.hpp"
#include "paddle.hpp"

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

    this->scene->setSceneRect(0,0,this->sceneWidth,this->sceneHeight);
    this->draw();

    connect(this->timer, SIGNAL(timeout()), this->scene, SLOT(advance()));
    this->timer->start(10);
}

BreakoutWindow::~BreakoutWindow()
{
    delete ui;
}

void BreakoutWindow::draw()
{
    QPen pen(Qt::blue);

    QLineF top(this->scene->sceneRect().topLeft(), this->scene->sceneRect().topRight());
    QLineF left(this->scene->sceneRect().bottomLeft(), this->scene->sceneRect().topLeft());
    QLineF right(this->scene->sceneRect().topRight(), this->scene->sceneRect().bottomRight());
    QLineF bottom(this->scene->sceneRect().bottomLeft(), this->scene->sceneRect().bottomRight());

    this->scene->addLine(top, pen);
    this->scene->addLine(left, pen);
    this->scene->addLine(right, pen);
    this->scene->addLine(bottom, pen);

    this->scene->addItem(new Ball(100, 100));
    this->scene->addItem(new Paddle);

}
