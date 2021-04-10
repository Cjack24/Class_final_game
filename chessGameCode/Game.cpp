#include "Game.h"
#include <QTime>

Game::Game(){
    board_ = new Board();
    turn = 0;
    qsrand(static_cast<unsigned>(QTime::currentTime().msec()));
}

void Game::step(){
    board_->update();
    turn++;
}

std::vector<Cell*> Game::get_cells(){
    return board_ ->get_cells();
}
