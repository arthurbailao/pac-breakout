#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = 0);

    enum Players {
        Human = 1,
        Computer = 2
    };

    inline Players currentTurn() const
    {
        return this->turn;
    }
    
signals:
    
public slots:

private:
    Players turn;
    Players lastHit;
    
};

#endif // CONTROLLER_HPP
