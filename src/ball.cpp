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
    this->setPos(this->x, this->y);
    this->direction = QLineF(QPointF(this->x, this->y), QPointF(this->x-1, this->y));
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

int	Ball::type() const
{
    return BreakoutItem::Ball;
}

void Ball::collision()
{
//    QList<BreakoutItem*> items = this->collidingItems();
//    if(items.isEmpty())
//        return;
    if(this->collidingItems().isEmpty())
        return;

    BreakoutItem* item = this->collidingItems().first();

    if(item->type() == BreakoutItem::Wall || item->type() == BreakoutItem::Paddle) {
        QPointF p1 = this->direction.p1();
        this->direction.setP1(this->direction.p2());
        this->direction.setP2(p1);
    }
}

void Ball::next()
{
    qreal angle = this->direction.angle()*M_PI/180.0;
//    qDebug() << this->direction.angle();
    this->direction.setP1(this->direction.p2());
    this->direction.setP2(QPointF(this->direction.p1().x() + 1.5*cos(angle), this->direction.p1().y() - 1.5*sin(angle)));
    this->setPos(this->direction.p2());
}
