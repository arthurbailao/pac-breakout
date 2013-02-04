#ifndef BALL_HPP
#define BALL_HPP

#include "breakout_item.hpp"

//Classe que representa a bola no jogo.
class Ball : public BreakoutItem
{
    Q_OBJECT
public:
    explicit Ball(qreal x, qreal y, QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/);
    virtual void advance(int phase);
    virtual QPainterPath shape() const;
    virtual int	type() const;

    //Atribui uma direção à bola.
    void setDirection(const QPointF& p1, const QPointF& p2);
    void setDirection(const QLineF& line);

    //Controle para que apenas uma colisão aconteça.
    inline void enableCollisions()
    {
        this->collisionEnabled = true;
    }

protected:
    virtual QPointF center() const;
    virtual void collisionEvent(const QList<BreakoutItem*>& items);

signals:
    //Mudança de posição da bola.
    void posChanged(QString);
    //Colisão com o paddle do jogador.
    void humanPaddleHit();
    //Colisão com o paddle do computador.
    void computerPaddleHit();
    //Colisão com a parede da esquerda.
    void leftWallHit();
    //Colisão com a parede da direita.
    void rightWallHit();
    //Colisão com as paredes de cima e de baixo.
    void topBottomWallHit();
    
public slots:
    void setBallSpeed(int ballSpeed);

private:
    //Classe que representa a direção da bola.
    class Direction : public QLineF
    {
    public:
        Direction();
        Direction(const QPointF& p1, const QPointF& p2);
        Direction(qreal x1, qreal y1, qreal x2, qreal y2);
        Direction(const QLineF& line);

        //Inverte o sentido.
        void invert();
        //Calcula o ângulo de reflexão a partir da normal.
        void reflect(const QLineF& normal);
    };

    //Atributos
    const qreal radius;
    qreal speed;
    Direction direction;
    bool collisionEnabled;

    //Método de avanço da bola.
    void next();
    
};

#endif // BALL_HPP
