#include <gtest/gtest.h>

#include <engine/Game.hpp>

using namespace minesweeper;

TEST(BoardViewDimensions, MatchesGameDimensions)
{
    const auto game = Game::from_mines(4, 3, {});
    const auto view = game.board_view();

    EXPECT_EQ(view.width(), 4);
    EXPECT_EQ(view.height(), 3);
}

TEST(BoardViewCells, ShowsHiddenCellsAsHidden)
{
    const auto game = Game::from_mines(3, 3, {{1, 1}});
    const auto view = game.board_view();
    const auto& cell = view.cell_at({1, 1});

    EXPECT_EQ(cell.state, CellViewState::hidden);
    EXPECT_FALSE(cell.has_mine);
    EXPECT_EQ(cell.adjacent_mines, 0);
}

TEST(BoardViewCells, ShowsFlaggedCellsAsFlagged)
{
    auto game = Game::from_mines(3, 3, {{1, 1}});
    game.make_action(ToggleFlagAction{{1, 1}});
    const auto view = game.board_view();
    const auto& cell = view.cell_at({1, 1});

    EXPECT_EQ(cell.state, CellViewState::flagged);
    EXPECT_FALSE(cell.has_mine);
    EXPECT_EQ(cell.adjacent_mines, 0);
}

TEST(BoardViewCells, ShowsRevealedNumber)
{
    auto game = Game::from_mines(3, 3, {{1, 1}});
    game.make_action(RevealAction{{0, 0}});
    const auto view = game.board_view();
    const auto& cell = view.cell_at({0, 0});

    EXPECT_EQ(cell.state, CellViewState::revealed);
    EXPECT_FALSE(cell.has_mine);
    EXPECT_EQ(cell.adjacent_mines, 1);
}

TEST(BoardViewCells, ShowsRevealedMine)
{
    auto game = Game::from_mines(3, 3, {{1, 1}});
    game.make_action(RevealAction{{1, 1}});
    const auto view = game.board_view();
    const auto& cell = view.cell_at({1, 1});

    EXPECT_EQ(cell.state, CellViewState::revealed);
    EXPECT_TRUE(cell.has_mine);
}

TEST(BoardViewAccess, RejectsNegativePosition)
{
    const auto game = Game::from_mines(3, 3, {});
    const auto view = game.board_view();

    EXPECT_THROW(view.cell_at({-1, 0}), std::out_of_range);
}

TEST(BoardViewAccess, RejectsPositionOutsideBoard)
{
    const auto game = Game::from_mines(3, 3, {});
    const auto view = game.board_view();

    EXPECT_THROW(view.cell_at({0, 3}), std::out_of_range);
}

TEST(BoardViewNeighbors, ReturnsAdjacentPositions)
{
    const auto game = Game::from_mines(3, 3, {});
    const auto view = game.board_view();

    EXPECT_EQ(view.get_neighbors({0, 0}).size(), 3);
    EXPECT_EQ(view.get_neighbors({0, 1}).size(), 5);
    EXPECT_EQ(view.get_neighbors({1, 1}).size(), 8);
}

TEST(BoardViewNeighbors, RejectsInvalidPosition)
{
    const auto game = Game::from_mines(3, 3, {});
    const auto view = game.board_view();

    EXPECT_THROW(view.get_neighbors({-1, 0}), std::out_of_range);
}
