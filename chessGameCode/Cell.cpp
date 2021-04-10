#include "Cell.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

Cell::Cell(int x,int y){
    x_ = x;
    y_ = y;
    int randomchance = rand() % 101;
    if (randomchance <= 25){
        is_alive = true;
        r_ = rand() % 255;
        g_ = rand() % 255;
        b_ = rand() % 255;
    }else{
        is_alive = false;
        r_ = 255;
        g_ = 255;
        b_ = 255;
    }
    color_ = QColor(r_,g_,b_);
}

void Cell::kill(){
    is_alive = false;
    this -> change_color(255,255,255);
}

void Cell::revive(){
    is_alive = true;
}
void Cell::set_neighbors(std::vector<Cell*> neighbors){
    neighbors_ = neighbors;
}

std::vector<int> Cell::get_position(){
    std::vector<int> position;
    position.push_back(x_);
    position.push_back(y_);
    return position;
}

void Cell::update_cell(){
    int alive = 0;
    std::vector<int> new_color = {0,0,0};
    std::vector<int> temp_color = {0,0,0};
    std::vector<Cell*>::iterator it;
    for (it = neighbors_.begin(); it != neighbors_.end(); ++it){
        if((*it) -> is_cell_alive()){
            temp_color = (*it)->get_color();
            if(new_color.at(0) == 0){
                new_color.at(0) = temp_color.at(0);
            }else{
                new_color.at(0) = new_color.at(0) + ((*it)->get_color().at(0));
            }
            if(new_color.at(1) == 0){
                new_color.at(1) = temp_color.at(1);
            }else{
                new_color.at(1) = new_color.at(1) + ((*it)->get_color().at(1));
            }
            if(new_color.at(2) == 0){
                new_color.at(2) = temp_color.at(2);
            }else{
                new_color.at(2) = new_color.at(2) + ((*it)->get_color().at(2));
            }
            alive++;
        }
    }
    if(is_alive){
        if(alive < 2 || alive > 3){
            this -> kill();
        }
    }else{
        if(alive == 3){
            int r = round(new_color.at(0)/(alive));
            int g = round(new_color.at(1)/(alive));
            int b = round(new_color.at(2)/(alive));
            //random mutations
            int pos_or_neg = rand() % 2;
            if(pos_or_neg == 1){
                r  += (rand() % 20 + 2) * -1;
            }else{
                r  += (rand() % 20 + 2);
            }
            if(pos_or_neg == 1){
                g  += (rand() % 20 + 2) * -1;
            }else{
                g  += (rand() % 20 + 2);
            }
            if(pos_or_neg == 1){
                b  += (rand() % 20 + 2) * -1;
            }else{
                b  += (rand() % 20 + 2);
            }

            this -> revive();
            this -> change_color(r,g,b);
        }
    }
    update();
}

void Cell::change_color(int r, int g, int b){
    if(is_alive){
        if (r > 254){
            r = 254;
        }
        if (g > 254){
            g = 254;
        }
        if (b > 254){
            b = 254;
        }
    }
    r_ = r;
    g_ = g;
    b_ = b;
    color_ = QColor(r,g,b);
}
std::vector<int> Cell::get_color(){
    std::vector<int> color = {r_,g_,b_};
    return color;
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit cell_pressed(this);
    if(event->button() == Qt::MouseButton::RightButton){
        qDebug() << "cell killed";
        this -> kill();
        this -> change_color(255,255,255);
    }else if(event->button() == Qt::MouseButton::LeftButton){
        qDebug() << "cell revived";
        this -> revive();
        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;
        this -> change_color(r,g,b);
    }

    update();
}

QRectF Cell::boundingRect() const
{
    return QRectF(x_, y_, height_, width_);
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, height_, width_);
    return path;
}
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush brush = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(color_));
    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->height_));
    painter->setBrush(brush);
}
