#include "paddle.hpp"

#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Paddle::Paddle(int topLimit, int bottomLimit, QGraphicsItem* parent) :
    BreakoutItem(parent),
    width(15.0), height(40.0),
    topLimit(topLimit), bottomLimit(bottomLimit)
{
}

QRectF Paddle::boundingRect() const
{
    return QRectF(0, 0, this->width, this->height);
}

void Paddle::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
     const int startAngle = 270 * 16;
     const int spanAngle = 180 * 16;
     painter->setBrush(Qt::SolidPattern);
     painter->drawPie(this->boundingRect(), startAngle, spanAngle);
}

QPainterPath Paddle::shape() const
{
    return QGraphicsObject::shape();
}

int Paddle::type() const
{
    return BreakoutItem::BreakoutPaddle;
}

QPointF Paddle::center() const
{
    QRectF rect = this->boundingRect();
    return this->mapToScene(QPointF(rect.left() - 10.0, (rect.top() + rect.bottom())/2.0));
}

void Paddle::move(qreal y)
{
    if(y <= this->topLimit || (y+ this->boundingRect().height()) >= this->bottomLimit)
        return;
    this->setY(y);
}

PlayerPaddle::PlayerPaddle(int topLimit, int bottomLimit, QGraphicsItem* parent) :
    Paddle(topLimit, bottomLimit, parent)
{

}

bool PlayerPaddle::eventFilter(QObject* /*obj*/, QEvent* event)
{
    if(event->type() == QEvent::GraphicsSceneMouseMove) {
        QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        this->move(mouseEvent->scenePos().y());
    }
    else if(event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Up) {
            this->move(this->y() - 10);
        }
        else if(keyEvent->key() == Qt::Key_Down) {
            this->move(this->y() + 10);
        }
    }

    return false;
}
