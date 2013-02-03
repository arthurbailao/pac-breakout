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

    void setDirection(const QPointF& p1, const QPointF& p2);
    void setDirection(const QLineF& line);

protected:
    virtual QPointF center() const;
    virtual void collisionEvent(const QList<BreakoutItem*>& items);
    
signals:
    void posChanged(QString);
    
public slots:
    void setBallSpeed(int ballSpeed);

private:
    class Direction : public QLineF
    {
    public:
        Direction();
        Direction(const QPointF& p1, const QPointF& p2);
        Direction(qreal x1, qreal y1, qreal x2, qreal y2);
        Direction(const QLineF& line);

        void invert();
        void reflect(const QLineF& normal);
    };

    const qreal radius;
    qreal speed;
    Direction direction;

//    void collision();
    void next();
    
};

#endif // BALL_HPP
