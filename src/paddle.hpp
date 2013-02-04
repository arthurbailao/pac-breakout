#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "breakout_item.hpp"

//Classe base para os paddles do jogador e do computador
class Paddle : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Paddle(int topLimit, int bottomLimit, QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const;
    virtual int type() const;

protected:

    virtual QPointF center() const;
    //Move o paddle, respeitandos os limites superior e inferior.
    void move(qreal y);

signals:
    //É emitido quando a posição do paddle muda.
    void posChanged(QString);
    
public slots:

private:
    const qreal width, height;
    const int topLimit, bottomLimit;
    
};

//Classe derivada que representa o paddle do jogador.
class HumanPaddle : public Paddle
{
    Q_OBJECT
public:
    explicit HumanPaddle(int topLimit, int bottomLimit, QGraphicsItem* parent = 0);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);

protected:
    //Captura o evento de movimento do mouse e teclado.
    virtual bool eventFilter(QObject* obj, QEvent* event);

};

//Classe derivada que representa o paddle do computador.
class ComputerPaddle : public Paddle
{
    Q_OBJECT
public:
    explicit ComputerPaddle(int topLimit, int bottomLimit, QGraphicsItem* parent = 0);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
};


#endif // PADDLE_HPP
