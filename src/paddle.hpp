#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "breakout_item.hpp"

class Paddle : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Paddle(QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
    virtual QPainterPath shape() const;
    virtual int type() const;

protected:
    virtual QPointF center() const;
    
signals:
    
public slots:

private:
    const qreal width, height;
    
};

class PlayerPaddle : public Paddle
{
    Q_OBJECT
public:
    explicit PlayerPaddle(QGraphicsItem* parent = 0);

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event);

};


#endif // PADDLE_HPP
