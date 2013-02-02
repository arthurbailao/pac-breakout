#ifndef BALL_HPP
#define BALL_HPP

#include "breakout_item.hpp"

class Ball : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Ball(qreal x, qreal y, QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
    virtual void advance(int phase);
    virtual QPainterPath shape() const;
    virtual int	type() const;

protected:
    virtual QPointF center() const;
    
signals:
    
public slots:

private:
    class Direction : public QLineF
    {
    public:
        Direction();
        Direction(const QPointF& p1, const QPointF& p2);
        Direction(qreal x1, qreal y1, qreal x2, qreal y2);
        Direction(const QLine& line);

        void invert();
    };

    const qreal radius;
    Direction direction;

    void collision();
    void next();
    
};

#endif // BALL_HPP
