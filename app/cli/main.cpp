#include <iostream>

#include <Board.hpp>

int main()
{
    std::cout << "Starting minesweeper...";

    minesweeper::Board board(5, 5, 5);
    board.print_board();
    return 0;
}
