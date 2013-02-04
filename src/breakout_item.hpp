#ifndef BREAKOUT_ITEM_HPP
#define BREAKOUT_ITEM_HPP

#include <QGraphicsObject>

//Classe base de todos os items do jogo.
class BreakoutItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit BreakoutItem(QGraphicsItem* parent = 0);

    //Retorna o ponto central do item. Esse ponto é utilizado no cálculo da direção de reflexão da bola.
    virtual QPointF center() const;
    //Método que chama o evento de colisão.
    virtual void advance(int phase);
    
protected:
    //Tipos de item existentes no jogo.
    enum {
        BreakoutBall = UserType,
        BreakoutPaddle = UserType + 1,
        BreakoutWall = UserType + 2,
        BreakoutBrick = UserType + 3
    };

    //Método chamdo quando uma colisão acontece. A implementação default não faz nada.
    virtual void collisionEvent(const QList<BreakoutItem*>& items);
    //Retorna os items colididos.
    QList<BreakoutItem*> collidingItems(Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
    
};

#endif // BREAKOUT_ITEM_HPP
