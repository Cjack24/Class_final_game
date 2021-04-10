#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QTimer>
#include "Board.h"
#include "Game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UI; }
QT_END_NAMESPACE

class UI : public QMainWindow
{
    Q_OBJECT

public:
    UI(QWidget *parent = nullptr);
    ~UI();

private slots:
    void On_step_btn_click();
    void On_play_btn_click();
    void On_pause_btn_click();
    void slider_change(int);
    void slider_released();
    void slider_pressed();
    void cell_pressedSlot(Cell* cell);

private:
    QRect* rect;
    QGraphicsRectItem* rect1;
    QGraphicsRectItem* rect2;
    QGraphicsRectItem* rect3;
    QGraphicsRectItem* rect4;
    QGraphicsRectItem* rect5;
    QGraphicsRectItem* rect6;
    QGraphicsRectItem* rect7;
    QGraphicsRectItem* rect8;
    QGraphicsRectItem* rect9;
    QGraphicsRectItem* rect10;
    QGraphicsRectItem* rect11;
    int which_rect = 1;
    double speed;
    Game *game_;
    QTimer *timer;
    Ui::UI *ui;
    QGraphicsScene *scene;
};
#endif // UI_H
