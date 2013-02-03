#include "ball.hpp"
#include "wall.hpp"
#include "brick.hpp"

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
    this->direction = Direction(QPointF(x, y), QPointF(x-0.2, y-1));
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
    BreakoutItem::advance(phase);

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
    return BreakoutItem::BreakoutBall;
}

void Ball::collisionEvent(const QList<BreakoutItem*>& items)
{
    if(items.first()->type() == BreakoutItem::BreakoutWall) {
        Wall* wall = static_cast<Wall*>(items.first());
        if(!wall->isSolid())
            return;
        QLineF normal;
        if(this->y() < this->scene()->height()/2)
            normal = QLineF::fromPolar(1.0, 90.0);
        else
            normal = QLineF::fromPolar(1.0, 270.0);

        this->direction.reflect(normal);
    }
    else if(items.first()->type() == BreakoutItem::BreakoutPaddle) {
        QLineF normal(this->center(), items.first()->center());
        this->direction.reflect(normal);
    }
    else if(items.first()->type() == BreakoutItem::BreakoutBrick) {
        QVector<QPointF> solidBrickCenters;
        Q_FOREACH(BreakoutItem* item, items) {
            if(item->type() == BreakoutItem::BreakoutBrick && !static_cast<Brick*>(item)->isDestroyed())
                solidBrickCenters << item->center();
        }
        QLineF normal;
        if(solidBrickCenters.size() < 1)
            return;
        else if(solidBrickCenters.size() == 1)
            normal = QLineF(this->center(), solidBrickCenters.first());
        else {
            QPolygonF polygon(solidBrickCenters);
            normal = QLineF(this->center(), polygon.boundingRect().center());
        }
        this->direction.reflect(normal);
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

void Ball::Direction::reflect(const QLineF& normal)
{
    qreal rotationAngle = 2.0 * this->angleTo(normal);
    this->invert();
    this->setAngle(this->angle() + rotationAngle);
}
