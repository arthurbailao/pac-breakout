#include "breakout_item.hpp"

#include <QGraphicsScene>

BreakoutItem::BreakoutItem(QGraphicsItem* parent) :
    QGraphicsObject(parent)
{
}

QList<BreakoutItem*> BreakoutItem::collidingItems(Qt::ItemSelectionMode mode) const
{
    QList<BreakoutItem*> result;
    QList<QGraphicsItem*> items = this->scene()->collidingItems(this, mode);

    if(items.empty())
        return result;

    Q_FOREACH(QGraphicsItem* item, items) {
        result.push_back(static_cast<BreakoutItem*>(item));
    }
    return result;
}
