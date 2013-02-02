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
    qreal x, y;
    const qreal radius;
    QLineF direction;

    void collision();
    void next();
    
};

#endif // BALL_HPP
