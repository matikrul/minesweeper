#include <iostream>

#include <Board.hpp>

int main()
{
    std::cout << "Starting minesweeper...\n";

    minesweeper::Board board(5, 5, 5);
    board.reveal({0, 0});
    board.print_board();
    return 0;
}
