#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

class Board{
public:
    Board();
    int get_population();
    std::vector<Cell*> get_cells();
    Cell* find_cell(int,int);
    std::vector<Cell*> find_neighbors(Cell* cell);
    std::vector<Cell*> update_next_board();
    void update();
private:
    std::vector<Cell*> board_;
    std::vector<Cell*> next_board_;

};

#endif // BOARD_H
