#include <gtest/gtest.h>

#include <ai/encoding/BoardEncoder.hpp>
#include <engine/Game.hpp>

using namespace minesweeper;

TEST(BoardEncoder, EncodesHiddenCells)
{
    const auto game = Game::from_mines(2, 2, {{0, 0}});
    const BoardEncoder encoder;

    EXPECT_EQ(encoder.encode(game.board_view()),
              std::vector<float>({-1.0F, -1.0F, -1.0F, -1.0F}));
}

TEST(BoardEncoder, EncodesFlaggedCells)
{
    auto game = Game::from_mines(2, 2, {{0, 0}});
    game.make_action(ToggleFlagAction{{0, 0}});
    const BoardEncoder encoder;

    EXPECT_EQ(encoder.encode(game.board_view()),
              std::vector<float>({-2.0F, -1.0F, -1.0F, -1.0F}));
}

TEST(BoardEncoder, EncodesRevealedCells)
{
    auto game = Game::from_mines(3, 3, {{1, 1}});
    game.make_action(RevealAction{{0, 0}});
    const BoardEncoder encoder;

    EXPECT_EQ(encoder.encode(game.board_view()), std::vector<float>({
        1.0F, -1.0F, -1.0F,
        -1.0F, -1.0F, -1.0F,
        -1.0F, -1.0F, -1.0F
    }));
}

TEST(BoardEncoder, EncodesCellsInRowMajorOrder)
{
    auto game = Game::from_mines(3, 2, {{0, 1}, {1, 2}});
    game.make_action(RevealAction{{0, 0}});
    game.make_action(RevealAction{{1, 0}});
    const BoardEncoder encoder;

    EXPECT_EQ(encoder.encode(game.board_view()), std::vector<float>({
        1.0F, -1.0F, -1.0F,
        1.0F, -1.0F, -1.0F
    }));
}

TEST(BoardEncoder, EncodesMixedCellStates)
{
    auto game = Game::from_mines(3, 3, {{1, 1}});
    game.make_action(RevealAction{{0, 0}});
    game.make_action(ToggleFlagAction{{0, 1}});
    const BoardEncoder encoder;

    EXPECT_EQ(encoder.encode(game.board_view()), std::vector<float>({
        1.0F, -2.0F, -1.0F,
        -1.0F, -1.0F, -1.0F,
        -1.0F, -1.0F, -1.0F
    }));
}

TEST(BoardEncoder, RejectsRevealedMine)
{
    auto game = Game::from_mines(2, 2, {{0, 0}});
    game.make_action(RevealAction{{0, 0}});
    const BoardEncoder encoder;

    EXPECT_THROW(encoder.encode(game.board_view()), std::logic_error);
}
