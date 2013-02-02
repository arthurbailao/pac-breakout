#include "breakout_item.hpp"

#include <QGraphicsScene>

BreakoutItem::BreakoutItem(QGraphicsItem* parent) :
    QGraphicsObject(parent)
{
}

QPointF BreakoutItem::center() const
{
    return this->boundingRect().center();
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

void BreakoutItem::advance(int phase)
{
    if(!phase) return;

    QList<BreakoutItem*> items = this->collidingItems();
    if(items.isEmpty())
        return;

    this->collisionEvent(items);
}

void BreakoutItem::collisionEvent(const QList<BreakoutItem*>& /*items*/)
{

}

