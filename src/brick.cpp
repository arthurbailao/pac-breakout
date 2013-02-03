#include "brick.hpp"

#include <QPainter>

Brick::Brick(int x, int y, QGraphicsItem *parent) :
    BreakoutItem(parent),
    width(10.0), height(20.0),
    color(),
    destroyed(false)
{
    this->setPos(x, y);

    QList<Qt::GlobalColor> colors;
    colors << Qt::darkGray << Qt::gray << Qt::lightGray << Qt::red << Qt::green << Qt::blue << Qt::cyan << Qt::magenta <<
              Qt::yellow << Qt::darkRed << Qt::darkGreen << Qt::darkBlue << Qt::darkCyan << Qt::darkMagenta << Qt::darkYellow;
    this->color = colors[qrand() % colors.length()];
}

QRectF Brick::boundingRect() const
{
    return QRectF(0, 0, this->width, this->height);
}

void Brick::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setBrush(QBrush(this->color));
    painter->setPen(Qt::black);
    painter->drawRect(this->boundingRect());
}

QPointF Brick::center() const
{
    return this->mapToScene(this->boundingRect().center());
}

int	Brick::type() const
{
    return BreakoutItem::BreakoutBrick;
}

void Brick::collisionEvent(const QList<BreakoutItem*>& items)
{
    if(items.first()->type() == BreakoutItem::BreakoutBall) {
        this->destroy();
    }
}

void Brick::destroy()
{
    this->destroyed = true;
    this->hide();
}
