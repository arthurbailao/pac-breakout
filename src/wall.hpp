#ifndef WALL_HPP
#define WALL_HPP

#include "breakout_item.hpp"

class Wall : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Wall(bool solid, const QPointF& p1, const QPointF& p2, QGraphicsItem* parent = 0);
    explicit Wall(bool solid, const QLineF& line, QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
    virtual QPainterPath shape() const;
    virtual int type() const;

    inline bool isSolid() const
    {
        return this->solid;
    }
private:
    QLineF line;
    bool solid;
};

#endif // WALL_HPP
