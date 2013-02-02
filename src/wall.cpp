#include "wall.hpp"

#include <QPainter>
#include <QDebug>

Wall::Wall(const QPointF& p1, const QPointF& p2, QGraphicsItem* parent) :
    BreakoutItem(parent),
    line(p1, p2)
{
}

Wall::Wall(const QLineF& line, QGraphicsItem* parent) :
    BreakoutItem(parent),
    line(line)
{
}

QRectF Wall::boundingRect() const
{
    return QRectF(this->line.p1(), this->line.p2());
}

void Wall::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setPen(Qt::blue);
    painter->drawRect(QRectF(this->line.p1(), this->line.p2()));
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
//    return QGraphicsObject::shape();
}

int Wall::type() const
{
    return BreakoutItem::Wall;
}

QPointF Wall::center() const
{
//    qDebug() << this->collidingItems().first()->center();

    return this->mapToScene(this->boundingRect().center());

//    return items.first()->boundingRect().center();
}
