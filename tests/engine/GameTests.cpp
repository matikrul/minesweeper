#include <gtest/gtest.h>

#include <engine/Action.hpp>
#include <engine/Game.hpp>

using namespace minesweeper;

namespace {

void expect_revealed(const Game& game, Position position)
{
    const auto view = game.board_view();

    EXPECT_EQ(view.cell_at({0, 0}).state, CellViewState::revealed);
}

void expect_hidden(const Game& game, Position position)
{
    const auto view = game.board_view();

    EXPECT_NE(view.cell_at({0, 0}).state, CellViewState::revealed);
}

void flag_all_neighbors(Game& game, Position position)
{
    const auto view = game.board_view();

    for (const auto neighbor : view.get_neighbors(position))
    {
        game.make_action(ToggleFlagAction{neighbor});
    }
}

} // namespace

TEST(GameActions, RejectsInvalidFlagPosition)
{
    Game game(3, 3, 1);

    EXPECT_THROW(
        game.make_action(ToggleFlagAction{{-1, 0}}),
        std::out_of_range);
}

TEST(GameActions, RejectsInvalidRevealPosition)
{
    Game game(3, 3, 1);

    EXPECT_THROW(
        game.make_action(RevealAction{{3, 0}}),
        std::out_of_range);
}

TEST(GameActions, RejectsInvalidRevealNeighborsPosition)
{
    Game game(3, 3, 1);

    EXPECT_THROW(
        game.make_action(RevealNeighborsAction{{0, 3}}),
        std::out_of_range);
}

TEST(GameActions, ToggleFlagFlagsAndUnflagsCell)
{
    Game game(3, 3, 1);

    game.make_action(ToggleFlagAction{{1, 1}});
    EXPECT_TRUE(game.board().cell_at({1, 1}).is_flagged());

    game.make_action(ToggleFlagAction{{1, 1}});
    EXPECT_FALSE(game.board().cell_at({1, 1}).is_flagged());
}

TEST(GameActions, RevealMineLosesGame)
{
    auto game = Game::from_mines(
        3,
        3,
        {
            {1, 1}
        });

    const auto state = game.make_action(RevealAction{{1, 1}});

    EXPECT_EQ(state, GameState::lost);
    EXPECT_TRUE(game.board().cell_at({1, 1}).is_revealed());
    EXPECT_TRUE(game.board().cell_at({1, 1}).has_mine());
}

TEST(GameActions, RevealNeighborsDoesNothingWhenCellIsHidden)
{
    Game game(3, 3, 0);

    game.make_action(RevealNeighborsAction{{1, 1}});

    expect_hidden(game, {0, 0});
    expect_hidden(game, {1, 1});
    expect_hidden(game, {2, 2});
}

TEST(GameActions, RevealNeighborsLosesGameWhenFlagsMatchWrongMine)
{
    auto game = Game::from_mines(
        3,
        3,
        {
            {0, 0}
        });

    game.make_action(RevealAction{{1, 1}});
    game.make_action(ToggleFlagAction{{0, 1}});

    const auto state = game.make_action(RevealNeighborsAction{{1, 1}});

    EXPECT_EQ(state, GameState::lost);
    EXPECT_TRUE(game.board().cell_at({0, 0}).is_revealed());
    EXPECT_TRUE(game.board().cell_at({0, 0}).has_mine());
    EXPECT_TRUE(game.board().cell_at({0, 1}).is_flagged());
    expect_hidden(game, {0, 1});
}

TEST(GameActions, RevealNeighborsRevealsAdjacentCellsWhenFlagCountMatches)
{
    Game game(3, 3, 0);

    game.make_action(RevealAction{{1, 1}});
    game.make_action(RevealNeighborsAction{{1, 1}});

    expect_revealed(game, {0, 0});
    expect_revealed(game, {0, 1});
    expect_revealed(game, {0, 2});
    expect_revealed(game, {1, 0});
    expect_revealed(game, {1, 2});
    expect_revealed(game, {2, 0});
    expect_revealed(game, {2, 1});
    expect_revealed(game, {2, 2});
}

TEST(GameActions, RevealNeighborsDoesNothingWhenFlagCountDoesNotMatch)
{
    Game game(3, 3, 8);

    game.make_action(RevealAction{{1, 1}});
    game.make_action(ToggleFlagAction{{0, 0}});
    game.make_action(RevealNeighborsAction{{1, 1}});

    expect_hidden(game, {0, 1});
    expect_hidden(game, {0, 2});
    expect_hidden(game, {1, 0});
    expect_hidden(game, {1, 2});
    expect_hidden(game, {2, 0});
    expect_hidden(game, {2, 1});
    expect_hidden(game, {2, 2});
}

TEST(GameActions, RevealNeighborsSkipsFlaggedNeighbors)
{
    Game game(3, 3, 8);

    game.make_action(RevealAction{{1, 1}});
    flag_all_neighbors(game, {1, 1});

    const auto state = game.make_action(RevealNeighborsAction{{1, 1}});

    EXPECT_EQ(state, GameState::won);
    EXPECT_TRUE(game.board().cell_at({0, 0}).is_flagged());
    expect_hidden(game, {0, 0});
}