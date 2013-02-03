#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "breakout_item.hpp"

class Paddle : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Paddle(int topLimit, int bottomLimit, QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
    virtual QPainterPath shape() const;
    virtual int type() const;

protected:
    virtual QPointF center() const;
    void move(qreal y);

signals:
    void posChanged(QString);
    
public slots:

private:
    const qreal width, height;
    const int topLimit, bottomLimit;
    
};

class PlayerPaddle : public Paddle
{
    Q_OBJECT
public:
    explicit PlayerPaddle(int topLimit, int bottomLimit, QGraphicsItem* parent = 0);

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event);

};


#endif // PADDLE_HPP
