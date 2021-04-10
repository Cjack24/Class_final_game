#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game{
public:
    Game();
    void step();
    std::vector<Cell*> get_cells();
    int get_turn(){return turn;}
    int get_pop(){return board_->get_population();}
private:
    Board* board_;
    int turn;
};

#endif // GAME_H
