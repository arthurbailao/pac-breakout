#ifndef WALL_HPP
#define WALL_HPP

#include "breakout_item.hpp"

class Wall : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Wall(const QPointF& p1, const QPointF& p2, QGraphicsItem* parent = 0);
    explicit Wall(const QLineF& line, QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
    virtual QPainterPath shape() const;

protected:
    virtual QPointF center() const;

private:
    QLineF line;
};

#endif // WALL_HPP
