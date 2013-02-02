#ifndef BREAKOUT_ITEM_HPP
#define BREAKOUT_ITEM_HPP

#include <QGraphicsObject>

class BreakoutItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit BreakoutItem(QGraphicsItem* parent = 0);

    virtual QPointF center() const;
    virtual void advance(int phase);
    
protected:
    enum {
        BreakoutBall = UserType,
        BreakoutPaddle = UserType + 1,
        BreakoutWall = UserType + 2,
        BreakoutBrick = UserType + 3
    };

    virtual void collisionEvent(const QList<BreakoutItem*>& items);
    QList<BreakoutItem*> collidingItems(Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
    
};

#endif // BREAKOUT_ITEM_HPP
