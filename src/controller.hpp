#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>

//Essa classe controla o jogo (pontuação, número de bolas restantes, fim de jogo etc.).
//Além disso, emite sinais pra janela informando que esses atributos mudaram para atualizar os valores na tela.
class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = 0);

    //Tipos de jogadores
    enum Players {
        Human = 1,
        Computer = 2
    };

    //Método que retorna "de quem é a vez de sair com a bola"
    Players currentTurn() const;
    //Volta o jogo ao estado inicial.
    void resetGame();
    void setTotalBricks(int value);

signals:
    //Pontuação é alterada.
    void humanScoreChanged(QString);
    void computerScoreChanged(QString);
    //Número de bolas restantes é alterado.
    void remainingBallsChanged(QString);
    //Fim do jogo.
    void gameOver(Controller::Players);
    
public slots:
    //Controle de quem foi o último a bater na bola.
    void onHumanPaddleHit();
    void onComputerPaddleHit();
    //Soma pontos quando a bola bate na parede.
    void onTopBottomWallHit();
    //Tira pontos quando a bola sai pelas laterais.
    void onRightWallHit();
    void onLeftWallHit();
    //Soma pontos quando um tijolo é quebrado.
    void onBrickHit();

private:
    Players lastHit;
    int humanScore, computerScore;
    int remainingBalls;
    int totalBricks, remainingBricks;

    void addScore(int value);
    void updateRemainingBalls();
    void updateRemainingBricks();
    
};

#endif // CONTROLLER_HPP
