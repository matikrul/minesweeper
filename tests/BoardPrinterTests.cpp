#include <gtest/gtest.h>

#include <Board.hpp>
#include <BoardPrinter.hpp>

#include <iostream>
#include <sstream>

using namespace minesweeper;

namespace {

std::string printed_board(const Board& board)
{
    auto* original_buffer = std::cout.rdbuf();
    std::ostringstream output;
    std::cout.rdbuf(output.rdbuf());

    BoardPrinter::print(BoardView(board));

    std::cout.rdbuf(original_buffer);
    return output.str();
}

} // namespace

TEST(BoardPrinter, PrintsHiddenAndFlaggedCells)
{
    auto board = Board::from_mines(
        2,
        2,
        {
            {0, 0}
        });

    board.toggle_flag({0, 0});

    EXPECT_EQ(printed_board(board), "F . \n. . \n");
}

TEST(BoardPrinter, PrintsRevealedMineNumberAndBlank)
{
    auto board = Board::from_mines(
        3,
        1,
        {
            {0, 0}
        });

    board.reveal({0, 0});
    board.reveal({0, 1});
    board.reveal({0, 2});

    EXPECT_EQ(printed_board(board), "* 1 _ \n");
}