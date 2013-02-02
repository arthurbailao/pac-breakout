#include "paddle.hpp"

#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

Paddle::Paddle(QGraphicsItem* parent) :
    BreakoutItem(parent),
    width(15.0), height(40.0)
{
//    this->setPos(10, this->scene()->sceneRect().height()/2 - this->height/2);
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
    return BreakoutItem::Paddle;
}

QPointF Paddle::center() const
{
    QRectF rect = this->boundingRect();
//    qDebug() << this->collidingItems().first()->center();

    return this->mapToScene(QPointF(rect.left(), (rect.top() + rect.bottom())/2.0));
}

PlayerPaddle::PlayerPaddle(QGraphicsItem* parent) :
    Paddle(parent)
{

}

bool PlayerPaddle::eventFilter(QObject* /*obj*/, QEvent* event)
{
    if(event->type() == QEvent::GraphicsSceneMouseMove) {
        QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        this->setY(mouseEvent->scenePos().y());
    }
    else if(event->type() == QEvent::KeyPress) {

    }
    else if(event->type() == QEvent::KeyRelease) {

    }

    return false;
}
