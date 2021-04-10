#include "Board.h"


Board::Board(){
    Cell *cell;

    for(int y = 0; y < 15; y++){
        for(int x = 0; x < 27; x++){
           cell = new Cell(28*x,20*y);
           board_.push_back(cell);
        }
    }

    for(int i =0; i < 405; i++){
        board_.at(i)->set_neighbors(this->find_neighbors(board_.at(i)));
    }
    next_board_ = board_;
}

int Board::get_population(){
    int count = 0;
    std::vector<Cell*>::iterator it;
    for(it = board_.begin(); it != board_.end(); ++it){
        if((*it)->is_cell_alive())
            count++;
    }
    return count;
}

std::vector<Cell*> Board::get_cells(){
    return board_;
}

Cell* Board::find_cell(int x, int y){
    Cell* cell = nullptr;
    if(x < 0)
        x = 728;
    if(x  > 728)
        x = 0;
    if(y < 0)
        y = 280;
    if(y > 280)
        y = 0;

    std::vector<int> position = {x,y};

    std::vector<Cell*>::iterator it;
    for(it = board_.begin(); it != board_.end(); ++it){
        if((*it)->get_position() == position){
            cell = (*it);
        }
    }
    return cell;
}

std::vector<Cell*> Board::find_neighbors(Cell* cell){
    std::vector<Cell*> neighbors;
    std::vector<int> cell_position = cell->get_position();
    Cell * neighbor = nullptr;
    for(int x = -1; x < 2; x++){
        for(int y = -1; y < 2; y++){
            neighbor  = find_cell(cell_position.at(0)+(x*28),cell_position.at(1)+(y*20));
            if(neighbor != cell){
                neighbors.push_back(neighbor);
            }
        }
    }
    return neighbors;
}

std::vector<Cell*> Board::update_next_board(){

    std::vector<Cell*> temp_board = next_board_;

    for(int i = 0; i < 405; i++){
        temp_board.at(i)->update_cell();
    }

    return temp_board;
}

void Board::update(){
    board_= next_board_;
    next_board_ = update_next_board();
}
