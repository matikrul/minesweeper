#include <gtest/gtest.h>

#include <BoardView.hpp>
#include <Game.hpp>

using namespace minesweeper;

#include <gtest/gtest.h>

#include <Board.hpp>

using namespace minesweeper;

TEST(BoardTests, CreatesBoardWithCorrectDimensions)
{
    Board board(5, 4, 3);

    EXPECT_EQ(board.width(), 5);
    EXPECT_EQ(board.height(), 4);
}

TEST(BoardTests, RejectsNonPositiveWidth)
{
    EXPECT_THROW(
        Board(0, 5, 1),
        std::invalid_argument);
}

TEST(BoardTests, RejectsNonPositiveHeight)
{
    EXPECT_THROW(
        Board(5, 0, 1),
        std::invalid_argument);
}

TEST(BoardTests, RejectsNegativeMineCount)
{
    EXPECT_THROW(
        Board(5, 5, -1),
        std::invalid_argument);
}

TEST(BoardTests, RejectsTooManyMines)
{
    EXPECT_THROW(
        Board(3, 3, 9),
        std::invalid_argument);
}

TEST(BoardTests, RejectsMineCountThatLeavesNoSafeCell)
{
    EXPECT_THROW(
        Board(1, 1, 1),
        std::invalid_argument);
}

TEST(BoardTests, CellAtReturnsCell)
{
    Board board(3, 3, 1);

    const auto& cell = board.cell_at({1, 2});

    EXPECT_FALSE(cell.is_revealed());
    EXPECT_FALSE(cell.is_flagged());
    EXPECT_FALSE(cell.has_mine());
}

TEST(BoardTests, CellAtRejectsNegativeRow)
{
    Board board(3, 3, 1);

    EXPECT_THROW(
        board.cell_at({-1, 0}),
        std::out_of_range);
}

TEST(BoardTests, CellAtRejectsRowOutsideBoard)
{
    Board board(3, 3, 1);

    EXPECT_THROW(
        board.cell_at({3, 0}),
        std::out_of_range);
}

TEST(BoardTests, CellAtRejectsColumnOutsideBoard)
{
    Board board(3, 3, 1);

    EXPECT_THROW(
        board.cell_at({0, 3}),
        std::out_of_range);
}

TEST(BoardTests, CornerHasThreeNeighbors)
{
    Board board(3, 3, 1);

    const auto neighbors = board.get_neighbors({0, 0});

    EXPECT_EQ(neighbors.size(), 3);
}

TEST(BoardTests, EdgeHasFiveNeighbors)
{
    Board board(3, 3, 1);

    const auto neighbors = board.get_neighbors({0, 1});

    EXPECT_EQ(neighbors.size(), 5);
}

TEST(BoardTests, CenterHasEightNeighbors)
{
    Board board(3, 3, 1);

    const auto neighbors = board.get_neighbors({1, 1});

    EXPECT_EQ(neighbors.size(), 8);
}

TEST(BoardTests, GetNeighborsRejectsInvalidPosition)
{
    Board board(3, 3, 1);

    EXPECT_THROW(
        board.get_neighbors({-1, 0}),
        std::out_of_range);
}

TEST(BoardTests, FromMinesPlacesMines)
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

TEST(BoardTests, FromMinesCalculatesAdjacentMines)
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

TEST(BoardTests, FromMinesCalculatesAdjacentMinesCorrectly)
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

TEST(BoardTests, FromMinesRejectsInvalidMinePosition)
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

TEST(BoardTests, FromMinesRejectsNegativeMinePosition)
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

TEST(BoardTests, FromMinesRejectsDuplicateMine)
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

TEST(BoardTests, RevealRevealsCell)
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

TEST(BoardTests, RevealRevealsMine)
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

TEST(BoardTests, RevealDoesNotRevealFlaggedCell)
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

TEST(BoardTests, ToggleFlagFlagsHiddenCell)
{
    auto board = Board::from_mines(3, 3, {});

    board.toggle_flag({1, 1});

    EXPECT_TRUE(board.cell_at({1, 1}).is_flagged());
}

TEST(BoardTests, ToggleFlagUnflagsFlaggedCell)
{
    auto board = Board::from_mines(3, 3, {});

    board.toggle_flag({1, 1});
    board.toggle_flag({1, 1});

    EXPECT_FALSE(board.cell_at({1, 1}).is_flagged());
}

TEST(BoardTests, ToggleFlagDoesNotFlagRevealedCell)
{
    auto board = Board::from_mines(3, 3, {});

    board.reveal({1, 1});
    board.toggle_flag({1, 1});

    EXPECT_TRUE(board.cell_at({1, 1}).is_revealed());
    EXPECT_FALSE(board.cell_at({1, 1}).is_flagged());
}

TEST(BoardViewTest, RevealedCellContainsAdjacentMineCount)
{
    Game game(5, 5, 5);

    game.make_action(RevealAction{{2, 2}});

    const auto view = game.board_view();

    const auto& cell = view.cell_at({2, 2});

    EXPECT_EQ(cell.state, CellViewState::revealed);
}