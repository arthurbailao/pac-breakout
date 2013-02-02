#include "ball.hpp"

#include <QDebug>
#include <QGraphicsScene>
#include <QLineF>
#include <QPainter>

#include <qmath.h>
#define _USE_MATH_DEFINES

Ball::Ball(qreal x, qreal y, QGraphicsItem *parent) :
    BreakoutItem(parent),
    radius(5.0),
    direction()
{
    this->setPos(x, y);
    this->direction = Direction(QPointF(x, y), QPointF(x-1, y));
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
    if(this->collidingItems().isEmpty())
        return;

    BreakoutItem* item = this->collidingItems().first();

    if(item->type() == BreakoutItem::Wall) {
        this->direction.invert();
    }
    else if(item->type() == BreakoutItem::Paddle) {
        QLineF normal(this->center(), item->center());
        qreal rotationAngle = 2.0 * this->direction.angleTo(normal);
        this->direction.invert();
        this->direction.setAngle(this->direction.angle() + rotationAngle);

    }
}

void Ball::next()
{
    qreal angle = this->direction.angle()*M_PI/180.0;
    this->direction.setP1(this->direction.p2());
    this->direction.setP2(QPointF(this->direction.p1().x() + 1.5*cos(angle), this->direction.p1().y() - 1.5*sin(angle)));
    this->setPos(this->direction.p2());
}


Ball::Direction::Direction() :
    QLineF()
{
}

Ball::Direction::Direction(const QPointF& p1, const QPointF& p2) :
    QLineF(p1, p2)
{
}

Ball::Direction::Direction(qreal x1, qreal y1, qreal x2, qreal y2) :
    QLineF(x1, y1, x2, y2)
{
}

Ball::Direction::Direction(const QLine& line) :
    QLineF(line)
{
}

void Ball::Direction::invert()
{
    QPointF p1 = this->p1();
    this->setP1(this->p2());
    this->setP2(p1);
}
