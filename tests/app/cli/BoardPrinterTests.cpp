#include <gtest/gtest.h>

#include <BoardPrinter.hpp>
#include <engine/Game.hpp>

#include <iostream>
#include <sstream>

using namespace minesweeper;

namespace {

std::string printed_board(const Game& game)
{
    auto* original_buffer = std::cout.rdbuf();
    std::ostringstream output;
    std::cout.rdbuf(output.rdbuf());

    BoardPrinter::print(game.board_view());

    std::cout.rdbuf(original_buffer);
    return output.str();
}

} // namespace

TEST(BoardPrinter, PrintsHiddenAndFlaggedCells)
{
    auto game = Game::from_mines(2, 2, {{0, 0}});
    game.make_action(ToggleFlagAction{{0, 0}});

    EXPECT_EQ(printed_board(game), "F . \n. . \n");
}

TEST(BoardPrinter, PrintsRevealedMineNumberAndBlank)
{
    auto game = Game::from_mines(3, 1, {{0, 0}});
    game.make_action(RevealAction{{0, 0}});
    game.make_action(RevealAction{{0, 1}});
    game.make_action(RevealAction{{0, 2}});

    EXPECT_EQ(printed_board(game), "* 1 _ \n");
}
