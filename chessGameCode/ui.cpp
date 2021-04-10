#include "ui.h"
#include "ui_ui.h"

#include <QDebug>
#include <string>
#include <iomanip>
#include <sstream>

UI::UI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UI)
{
    ui->setupUi(this);

    //set up graphics window
    QGraphicsView * view = ui->graphicsView;
    scene = new QGraphicsScene;
    view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setScene(scene);
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    rect = new QRect(10,315,view->frameSize().width()-20,view->frameSize().height()-325);
    scene->addRect(*rect);

    rect1 = new QGraphicsRectItem(*rect);
    rect1 -> setRect(10,365,60, 0);

    rect2 = new QGraphicsRectItem(*rect);
    rect2 -> setRect(75,365,60, 0);

    rect3 = new QGraphicsRectItem(*rect);
    rect3 -> setRect(140,365,60, 0);

    rect4 = new QGraphicsRectItem(*rect);
    rect4 -> setRect(205,365,60,0);

    rect5 = new QGraphicsRectItem(*rect);
    rect5 -> setRect(270,365,60, 0);

    rect6 = new QGraphicsRectItem(*rect);
    rect6 -> setRect(335,365,60, 0);

    rect7 = new QGraphicsRectItem(*rect);
    rect7 -> setRect(400,365,60, 0);

    rect8 = new QGraphicsRectItem(*rect);
    rect8 -> setRect(465,365,60, 0);

    rect9 = new QGraphicsRectItem(*rect);
    rect9 -> setRect(530,365,60, 0);

    rect10 = new QGraphicsRectItem(*rect);
    rect10 -> setRect(595,365,60, 0);

    rect11 = new QGraphicsRectItem(*rect);
    rect11 -> setRect(660,365,60, 0);

    scene->addItem(rect1);
    scene->addItem(rect2);
    scene->addItem(rect3);
    scene->addItem(rect4);
    scene->addItem(rect5);
    scene->addItem(rect6);
    scene->addItem(rect7);
    scene->addItem(rect8);
    scene->addItem(rect9);
    scene->addItem(rect10);
    scene->addItem(rect11);
    //Initialize
    game_ = new Game();
    speed = 0;
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this,&UI::On_step_btn_click);//essentually presses the step button
    //BTNs
    connect(ui->step_btn, &QAbstractButton::clicked, this, &UI::On_step_btn_click);
    connect(ui->play_btn, &QAbstractButton::clicked, this, &UI::On_play_btn_click);
    connect(ui->pause_btn, &QAbstractButton::clicked, this, &UI::On_pause_btn_click);
    //SLIDER
    ui->Time_slider->setRange(0,19);
    connect(ui->Time_slider, &QAbstractSlider::sliderMoved, this, &UI::slider_change);
    connect(ui->Time_slider, &QAbstractSlider::sliderReleased, this, &UI::slider_released);
    connect(ui->Time_slider, &QAbstractSlider::sliderPressed, this, &UI::slider_pressed);

    std::vector<Cell*> cells = game_->get_cells();

    for(int x = 0; x < 405; x++){
       Cell *c = cells.at(x);
       scene->addItem(c);
       connect(c, &Cell::cell_pressed, this, &UI::cell_pressedSlot);
    }
    int pop = game_->get_pop();
    double popPercentage = (double(pop)/405);
    double scale = 0.01;  // i.e. round to nearest one-hundreth
    popPercentage = floor(popPercentage / scale + 0.5) * scale;
    std::string t = "Population: " + std::to_string(pop) + " ("+ std::to_string(popPercentage*100)+ "%)";
    QString qturn(t.c_str());
    ui->population_txt->setText(qturn);
    update();
}

UI::~UI()
{
    delete ui;
}


void UI::On_step_btn_click(){
    game_ -> step();

    std::string s = "Turn: " + std::to_string(game_->get_turn());
    QString qs(s.c_str());
    ui->turn_txt->setText(qs);

    int pop = game_->get_pop();
    double popPercentage = (double(pop)/405);
    double scale = 0.01;  // i.e. round to nearest one-hundreth
    popPercentage = floor(popPercentage / scale + 0.5) * scale;
    std::string t = "Population: " + std::to_string(pop) + " ("+ std::to_string(popPercentage*100)+ "%)";
    QString qturn(t.c_str());
    ui->population_txt->setText(qturn);

    if(which_rect == 1){
        rect1 -> setRect(10,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 2){
        rect2 -> setRect(75,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 3){
        rect3 -> setRect(140,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 4){
        rect4 -> setRect(205,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 5){
        rect5 -> setRect(270,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 6){
        rect6 -> setRect(335,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 7){
        rect7 -> setRect(400,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 8){
        rect8 -> setRect(465,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 9){
        rect9 -> setRect(530,365,60, -(75*popPercentage));
        which_rect++;
    } else if(which_rect == 10){
        rect10 -> setRect(595,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 11){
        rect11 -> setRect(660,365,60, -(75*popPercentage));
        which_rect++;
    }else if(which_rect == 12){
        int newHeight = rect2->rect().height();
        rect1 -> setRect(10,365,60, newHeight);
        newHeight = rect3->rect().height();
        rect2 -> setRect(75,365,60, newHeight);
        newHeight = rect4->rect().height();
        rect3 -> setRect(140,365,60, newHeight);
        newHeight = rect5->rect().height();
        rect4 -> setRect(205,365,60, newHeight);
        newHeight = rect6->rect().height();
        rect5 -> setRect(270,365,60, newHeight);
        newHeight = rect7->rect().height();
        rect6 -> setRect(335,365,60, newHeight);
        newHeight = rect8->rect().height();
        rect7 -> setRect(400,365,60, newHeight);
        newHeight = rect9->rect().height();
        rect8 -> setRect(465,365,60, newHeight);
        newHeight = rect10->rect().height();
        rect9 -> setRect(530,365,60, newHeight);
        newHeight = rect11->rect().height();
        rect10 -> setRect(595,365,60, newHeight);
        newHeight = -(75*popPercentage);
        rect11 -> setRect(660,365,60, newHeight);
    }
    scene -> update();
}

void UI::On_play_btn_click(){
    if(speed != 0)
        timer -> start(speed);
}

void UI::On_pause_btn_click(){
    timer -> stop();
}

void UI::slider_change(int position){
    if(position == 0){
        speed = position;//min 2 sec, max 100 milisec
     }else{
        speed = 2000 - position*100;
    }
    std::string s = "Speed: " + std::to_string(speed/1000) + " seconds per turn";
    QString qs(s.c_str());
    ui->speed_txt->setText(qs);
    scene -> update();
}

void UI::slider_released(){
    if(speed != 0)
        timer -> start(speed);
}

void UI::slider_pressed(){
    timer->stop();
}

void UI::cell_pressedSlot(Cell* cell){
    std::vector<int> pos = cell -> get_position();
    qDebug() << "cell pressed (" << pos.at(0) << "," << pos.at(1) << ")";

    int pop = game_->get_pop();
    double popPercentage = (double(pop)/405)*100;
    double scale = 0.01;  // i.e. round to nearest one-hundreth
    popPercentage = floor(popPercentage / scale + 0.5) * scale;
    std::string t = "Population: " + std::to_string(pop) + " ("+ std::to_string(popPercentage)+ "%)";
    QString qturn(t.c_str());
    ui->population_txt->setText(qturn);
    qDebug() << "pop update";
    scene -> update();
}

