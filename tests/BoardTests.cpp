#include <gtest/gtest.h>

#include <BoardView.hpp>
#include <Game.hpp>

using namespace minesweeper;

TEST(BoardViewTest, RevealedCellContainsAdjacentMineCount)
{
    Game game(5, 5, 5);

    game.make_action(RevealAction{{2, 2}});

    const auto view = game.board_view();

    const auto& cell = view.cell_at({2, 2});

    EXPECT_EQ(cell.state, CellViewState::revealed);
}