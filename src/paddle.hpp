#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "breakout_item.hpp"

class Paddle : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Paddle(int topLimit, int bottomLimit, QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const;
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

class HumanPaddle : public Paddle
{
    Q_OBJECT
public:
    explicit HumanPaddle(int topLimit, int bottomLimit, QGraphicsItem* parent = 0);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event);

};

class ComputerPaddle : public Paddle
{
    Q_OBJECT
public:
    explicit ComputerPaddle(int topLimit, int bottomLimit, QGraphicsItem* parent = 0);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
};


#endif // PADDLE_HPP
