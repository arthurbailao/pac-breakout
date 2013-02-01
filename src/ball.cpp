#include "ball.hpp"

#include <QDebug>
#include <QGraphicsScene>
#include <QLineF>
#include <QPainter>

#include <math.h>

Ball::Ball(qreal x, qreal y, QGraphicsItem *parent) :
    BreakoutItem(parent),
    x(x), y(y),
    angle(0.0),
    radius(5.0)
{
    this->setPos(this->mapToScene(this->x, this->y));
    this->setRotation(this->angle);


}

QRectF Ball::boundingRect() const
{
    return QRectF(0, 0, 2*this->radius, 2*this->radius);
}

void Ball::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->drawRect(this->boundingRect());
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(this->boundingRect());

}

void Ball::advance(int phase)
{
    if(!phase) return;



//    QPointF location = this->pos();
    this->collision();
    this->setPos(this->mapToParent(1,0));



}

QPainterPath Ball::shape() const
{
//    QPainterPath path;
//    path.addEllipse(this->boundingRect());
//    return path;
    return QGraphicsObject::shape();
}

QPointF Ball::center() const
{
    return this->mapToScene(this->boundingRect().center());
}

void Ball::collision()
{
    QList<BreakoutItem*> items = this->collidingItems();
    if(items.isEmpty())
        return;


//    this->setRotation(this->rotation()+180);
//    this->setPos(this->mapToParent(0,0));
    this->prepareGeometryChange();
    this->setRotation(this->rotation()+30);
//    this->setTransformOriginPoint(this->boundingRect().topLeft());
//    qDebug() << "Ball: " << this->center();
//    qDebug() << "Paddle: " << items.first()->center();

//    QLineF normalLine(this->center(), items.first()->center());
//    this->scene()->addLine(normalLine, QPen(QColor(Qt::blue)));



//    if(this->scene()->sceneRect().contains(this->boundingRect().center()))
//    if(items.size() < 2) {
//        qDebug() << static_cast<QGraphicsEllipseItem*>(items.first())->rect();
//    }
}
