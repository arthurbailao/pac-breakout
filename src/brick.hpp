#ifndef BRICK_HPP
#define BRICK_HPP

#include "breakout_item.hpp"

class Brick : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Brick(int x, int y, QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
    virtual int	type() const;

    void build();

    inline bool isDestroyed() const
    {
        return this->destroyed;
    }

protected:
    virtual QPointF center() const;
    virtual void collisionEvent(const QList<BreakoutItem*>& items);
    
signals:
    void imDestroyed();
    
public slots:

private:
    const qreal width, height;
    Qt::GlobalColor color;
    bool destroyed;

    void destroy();
};

#endif // BRICK_HPP
