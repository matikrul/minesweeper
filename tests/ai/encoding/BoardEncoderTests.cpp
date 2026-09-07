#include <gtest/gtest.h>

#include <Board.hpp>
#include <ai/encoder/BoardEncoder.hpp>

using namespace minesweeper;

TEST(BoardEncoder, EncodesHiddenCells)
{
    const auto board = Board::from_mines(
        2,
        2,
        {
            {0, 0}
        });

    const BoardView view(board);

    const BoardEncoder encoder;
    const auto encoded = encoder.encode(view);

    EXPECT_EQ(encoded, std::vector<float>({
        -1.0F, -1.0F,
        -1.0F, -1.0F
    }));
}

TEST(BoardEncoder, EncodesFlaggedCells)
{
    auto board = Board::from_mines(
        2,
        2,
        {
            {0, 0}
        });

    board.toggle_flag({0, 0});

    const BoardView view(board);

    const BoardEncoder encoder;
    const auto encoded = encoder.encode(view);

    EXPECT_EQ(encoded, std::vector<float>({
        -2.0F, -1.0F,
        -1.0F, -1.0F
    }));
}

TEST(BoardEncoder, EncodesRevealedCells)
{
    auto board = Board::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    board.reveal({0, 0});

    const BoardView view(board);

    const BoardEncoder encoder;
    const auto encoded = encoder.encode(view);

    EXPECT_EQ(encoded, std::vector<float>({
        1.0F, -1.0F, -1.0F,
        -1.0F, -1.0F, -1.0F,
        -1.0F, -1.0F, -1.0F
    }));
}

TEST(BoardEncoder, EncodesCellsInRowMajorOrder)
{
    auto board = Board::from_mines(
        3,
        2,
        {
            {0, 1},
            {1, 2}
        });

    board.reveal({0, 0});
    board.reveal({1, 0});

    const BoardView view(board);

    const BoardEncoder encoder;
    const auto encoded = encoder.encode(view);

    EXPECT_EQ(encoded, std::vector<float>({
        1.0F, -1.0F, -1.0F,
        1.0F, -1.0F, -1.0F
    }));
}

TEST(BoardEncoder, EncodesMixedCellStates)
{
    auto board = Board::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    board.reveal({0, 0});
    board.toggle_flag({0, 1});

    const BoardView view(board);

    const BoardEncoder encoder;
    const auto encoded = encoder.encode(view);

    EXPECT_EQ(encoded, std::vector<float>({
        1.0F, -2.0F, -1.0F,
        -1.0F, -1.0F, -1.0F,
        -1.0F, -1.0F, -1.0F
    }));
}

TEST(BoardEncoder, RejectsRevealedMine)
{
    auto board = Board::from_mines(
        2,
        2,
        {
            {0, 0}
        });

    board.reveal({0, 0});

    const BoardView view(board);

    const BoardEncoder encoder;

    EXPECT_THROW(
        encoder.encode(view),
        std::logic_error);
}