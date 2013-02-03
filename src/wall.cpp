#include "wall.hpp"

#include <QPainter>
#include <QDebug>

Wall::Wall(bool solid, const QPointF& p1, const QPointF& p2, QGraphicsItem* parent) :
    BreakoutItem(parent),
    line(p1, p2),
    solid(solid)
{
}

Wall::Wall(bool solid, const QLineF& line, QGraphicsItem* parent) :
    BreakoutItem(parent),
    line(line),
    solid(solid)
{
}

QRectF Wall::boundingRect() const
{
    return QRectF(this->line.p1(), this->line.p2());
}

void Wall::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setPen(Qt::white);
    painter->drawRect(QRectF(this->line.p1(), this->line.p2()));
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}

int Wall::type() const
{
    return BreakoutItem::BreakoutWall;
}
