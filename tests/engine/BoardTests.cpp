#include <gtest/gtest.h>

#include <Board.hpp>

using namespace minesweeper;

TEST(BoardConstruction, CreatesBoardWithCorrectDimensions)
{
    Board board(5, 4, 3);

    EXPECT_EQ(board.width(), 5);
    EXPECT_EQ(board.height(), 4);
}

TEST(BoardConstruction, RejectsNonPositiveWidth)
{
    EXPECT_THROW(
        Board(0, 5, 1),
        std::invalid_argument);
}

TEST(BoardConstruction, RejectsNonPositiveHeight)
{
    EXPECT_THROW(
        Board(5, 0, 1),
        std::invalid_argument);
}

TEST(BoardConstruction, RejectsNegativeMineCount)
{
    EXPECT_THROW(
        Board(5, 5, -1),
        std::invalid_argument);
}

TEST(BoardConstruction, RejectsTooManyMines)
{
    EXPECT_THROW(
        Board(3, 3, 9),
        std::invalid_argument);
}

TEST(BoardConstruction, RejectsMineCountThatLeavesNoSafeCell)
{
    EXPECT_THROW(
        Board(1, 1, 1),
        std::invalid_argument);
}

TEST(BoardAccess, CellAtReturnsCell)
{
    Board board(3, 3, 1);

    const auto& cell = board.cell_at({1, 2});

    EXPECT_FALSE(cell.is_revealed());
    EXPECT_FALSE(cell.is_flagged());
    EXPECT_FALSE(cell.has_mine());
}

TEST(BoardAccess, CellAtRejectsNegativeRow)
{
    Board board(3, 3, 1);

    EXPECT_THROW(
        static_cast<void>(board.cell_at({-1, 0})),
        std::out_of_range);
}

TEST(BoardAccess, CellAtRejectsRowOutsideBoard)
{
    Board board(3, 3, 1);

    EXPECT_THROW(
        static_cast<void>(board.cell_at({3, 0})),
        std::out_of_range);
}

TEST(BoardAccess, CellAtRejectsColumnOutsideBoard)
{
    Board board(3, 3, 1);

    EXPECT_THROW(
        static_cast<void>(board.cell_at({0, 3})),
        std::out_of_range);
}

TEST(BoardNeighbors, CornerHasThreeNeighbors)
{
    Board board(3, 3, 1);

    const auto neighbors = board.get_neighbors({0, 0});

    EXPECT_EQ(neighbors.size(), 3);
}

TEST(BoardNeighbors, EdgeHasFiveNeighbors)
{
    Board board(3, 3, 1);

    const auto neighbors = board.get_neighbors({0, 1});

    EXPECT_EQ(neighbors.size(), 5);
}

TEST(BoardNeighbors, CenterHasEightNeighbors)
{
    Board board(3, 3, 1);

    const auto neighbors = board.get_neighbors({1, 1});

    EXPECT_EQ(neighbors.size(), 8);
}

TEST(BoardNeighbors, GetNeighborsRejectsInvalidPosition)
{
    Board board(3, 3, 1);

    EXPECT_THROW(
        static_cast<void>(board.get_neighbors({-1, 0})),
        std::out_of_range);
}

TEST(BoardMines, FromMinesPlacesMines)
{
    const auto board = Board::from_mines(
        3,
        3,
        {
            {0, 0},
            {2, 2}
        });

    EXPECT_TRUE(board.cell_at({0, 0}).has_mine());
    EXPECT_TRUE(board.cell_at({2, 2}).has_mine());
    EXPECT_FALSE(board.cell_at({1, 1}).has_mine());
}

TEST(BoardMines, FromMinesCalculatesAdjacentMines)
{
    const auto board = Board::from_mines(
        3,
        3,
        {
            {0, 0},
            {2, 2}
        });

    EXPECT_EQ(board.cell_at({1, 1}).adjacent_mines(), 2);
}

TEST(BoardMines, FromMinesCalculatesAdjacentMinesCorrectly)
{
    const auto board = Board::from_mines(
        3,
        3,
        {
            {0, 0},
            {0, 1},
            {1, 0}
        });

    EXPECT_EQ(board.cell_at({0, 0}).adjacent_mines(), 2);
    EXPECT_EQ(board.cell_at({0, 1}).adjacent_mines(), 2);
    EXPECT_EQ(board.cell_at({1, 1}).adjacent_mines(), 3);
    EXPECT_EQ(board.cell_at({2, 2}).adjacent_mines(), 0);
}

TEST(BoardMines, FromMinesRejectsInvalidMinePosition)
{
    EXPECT_THROW(
        Board::from_mines(
            3,
            3,
            {
                {3, 0}
            }),
        std::out_of_range);
}

TEST(BoardMines, FromMinesRejectsNegativeMinePosition)
{
    EXPECT_THROW(
        Board::from_mines(
            3,
            3,
            {
                {-1, 0}
            }),
        std::out_of_range);
}

TEST(BoardMines, FromMinesRejectsDuplicateMine)
{
    EXPECT_THROW(
        Board::from_mines(
            3,
            3,
            {
                {1, 1},
                {1, 1}
            }),
        std::invalid_argument);
}

TEST(BoardReveal, RevealsCell)
{
    auto board = Board::from_mines(
        3,
        3,
        {
            {0, 0}
        });

    board.reveal({2, 2});

    EXPECT_TRUE(board.cell_at({2, 2}).is_revealed());
}

TEST(BoardReveal, RevealsMine)
{
    auto board = Board::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    board.reveal({1, 1});

    EXPECT_TRUE(board.cell_at({1, 1}).is_revealed());
    EXPECT_TRUE(board.cell_at({1, 1}).has_mine());
}

TEST(BoardReveal, DoesNotRevealFlaggedCell)
{
    auto board = Board::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    board.toggle_flag({1, 1});
    board.reveal({1, 1});

    EXPECT_TRUE(board.cell_at({1, 1}).is_flagged());
    EXPECT_FALSE(board.cell_at({1, 1}).is_revealed());
}

TEST(BoardFlags, FlagsHiddenCell)
{
    auto board = Board::from_mines(3, 3, {});

    board.toggle_flag({1, 1});

    EXPECT_TRUE(board.cell_at({1, 1}).is_flagged());
}

TEST(BoardFlags, UnflagsFlaggedCell)
{
    auto board = Board::from_mines(3, 3, {});

    board.toggle_flag({1, 1});
    board.toggle_flag({1, 1});

    EXPECT_FALSE(board.cell_at({1, 1}).is_flagged());
}

TEST(BoardFlags, DoesNotFlagRevealedCell)
{
    auto board = Board::from_mines(3, 3, {});

    board.reveal({1, 1});
    board.toggle_flag({1, 1});

    EXPECT_TRUE(board.cell_at({1, 1}).is_revealed());
    EXPECT_FALSE(board.cell_at({1, 1}).is_flagged());
}
