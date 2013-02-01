#include "ball.hpp"

#include <QDebug>
#include <QGraphicsScene>
#include <QLineF>
#include <QPainter>

#include <qmath.h>
#define _USE_MATH_DEFINES

Ball::Ball(qreal x, qreal y, QGraphicsItem *parent) :
    BreakoutItem(parent),
    x(x), y(y),
    radius(5.0),
    direction()
{
    this->setPos(this->mapToScene(this->x, this->y));
    this->direction = QLineF(this->mapToScene(this->x, this->y), this->mapToScene(this->x+1.0, this->y));
}

QRectF Ball::boundingRect() const
{
    return QRectF(0, 0, 2*this->radius, 2*this->radius);
}

void Ball::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(this->boundingRect());
}

void Ball::advance(int phase)
{
    if(!phase) return;

    this->next();
    this->collision();
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}

QPointF Ball::center() const
{
    return this->mapToScene(this->boundingRect().center());
}

void Ball::collision()
{
//    QList<BreakoutItem*> items = this->collidingItems();
//    if(items.isEmpty())
//        return;
    if(this->collidingItems().isEmpty())
        return;

    QPointF p1 = this->direction.p1();
    this->direction.setP1(this->direction.p2());
    this->direction.setP2(p1);
}

void Ball::next()
{
    qreal angle = this->direction.angle()*M_PI/180.0;
    qDebug() << this->direction.angle();
    this->direction.setP1(this->direction.p2());
    this->direction.setP2(QPointF(this->direction.p1().x() + cos(angle), this->direction.p1().y() - sin(angle)));
    this->setPos(this->direction.p2());
}
