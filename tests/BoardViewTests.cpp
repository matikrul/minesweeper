#include <gtest/gtest.h>

#include <Board.hpp>
#include <engine/BoardView.hpp>

using namespace minesweeper;

TEST(BoardViewDimensions, MatchesBoardDimensions)
{
    const auto board = Board::from_mines(4, 3, {});

    const BoardView view(board);

    EXPECT_EQ(view.width(), 4);
    EXPECT_EQ(view.height(), 3);
}

TEST(BoardViewCells, ShowsHiddenCellsAsHidden)
{
    const auto board = Board::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    const BoardView view(board);

    const auto& cell = view.cell_at({1, 1});

    EXPECT_EQ(cell.state, CellViewState::hidden);
    EXPECT_FALSE(cell.has_mine);
    EXPECT_EQ(cell.adjacent_mines, 0);
}

TEST(BoardViewCells, ShowsFlaggedCellsAsFlagged)
{
    auto board = Board::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    board.toggle_flag({1, 1});

    const BoardView view(board);
    const auto& cell = view.cell_at({1, 1});

    EXPECT_EQ(cell.state, CellViewState::flagged);
    EXPECT_FALSE(cell.has_mine);
    EXPECT_EQ(cell.adjacent_mines, 0);
}

TEST(BoardViewCells, ShowsRevealedNumber)
{
    auto board = Board::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    board.reveal({0, 0});

    const BoardView view(board);
    const auto& cell = view.cell_at({0, 0});

    EXPECT_EQ(cell.state, CellViewState::revealed);
    EXPECT_FALSE(cell.has_mine);
    EXPECT_EQ(cell.adjacent_mines, 1);
}

TEST(BoardViewCells, ShowsRevealedMine)
{
    auto board = Board::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    board.reveal({1, 1});

    const BoardView view(board);
    const auto& cell = view.cell_at({1, 1});

    EXPECT_EQ(cell.state, CellViewState::revealed);
    EXPECT_TRUE(cell.has_mine);
}

TEST(BoardViewAccess, RejectsNegativePosition)
{
    const auto board = Board::from_mines(3, 3, {});
    const BoardView view(board);

    EXPECT_THROW(
        view.cell_at({-1, 0}),
        std::out_of_range);
}

TEST(BoardViewAccess, RejectsPositionOutsideBoard)
{
    const auto board = Board::from_mines(3, 3, {});
    const BoardView view(board);

    EXPECT_THROW(
        view.cell_at({0, 3}),
        std::out_of_range);
}