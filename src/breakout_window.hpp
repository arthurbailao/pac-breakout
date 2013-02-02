#ifndef BREAKOUT_WINDOW_HPP
#define BREAKOUT_WINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

namespace Ui {
class BreakoutWindow;
}

class BreakoutWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BreakoutWindow(QWidget *parent = 0);
    ~BreakoutWindow();
    
private:
    Ui::BreakoutWindow *ui;
    QGraphicsScene* scene;
    QTimer* timer;

    const qreal sceneWidth, sceneHeight;

    void draw();
    void drawWalls();
    void drawBall();
    void drawPaddles();
    void drawBricks();
};

#endif // BREAKOUT_WINDOW_HPP
