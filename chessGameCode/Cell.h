#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QGraphicsItem>

class Cell: public QObject, public QGraphicsItem {

    // this makes it so that we can emit signals
    Q_OBJECT

public:
    Cell(int,int);
    void kill();
    void revive();
    void set_neighbors(std::vector<Cell*> neighbors);
    std::vector<int> get_position();
    bool is_cell_alive() {return is_alive;};
    void update_cell();
    void change_color(int,int,int);
    std::vector<int> get_color();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
private:
    bool is_alive;
    std::vector<Cell*> neighbors_;
    QColor color_;
    int x_;
    int y_;
    int r_;
    int g_;
    int b_;
    static const int width_ = 30;
    static const int height_ = 28;
signals:
    void cell_pressed(Cell * cell);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CELL_H
