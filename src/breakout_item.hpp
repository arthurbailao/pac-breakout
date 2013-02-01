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
    QList<BreakoutItem*> collidingItems(Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
    
};

#endif // BREAKOUT_ITEM_HPP
