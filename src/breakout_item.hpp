#ifndef BREAKOUT_ITEM_HPP
#define BREAKOUT_ITEM_HPP

#include <QGraphicsObject>

class BreakoutItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit BreakoutItem(QGraphicsItem* parent = 0);

    virtual QPointF center() const = 0;
    
protected:
    enum {
        Ball = UserType,
        Paddle = UserType + 1,
        Wall = UserType + 2,
        Brick = UserType + 3
    };

    QList<BreakoutItem*> collidingItems(Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
    
};

#endif // BREAKOUT_ITEM_HPP
