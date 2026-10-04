#include <stdexcept>
#include <variant>
#include <vector>

#include <gtest/gtest.h>

#include <ai/decision/MaxScoreStrategy.hpp>

using namespace minesweeper;

namespace {

TEST(MaxScoreStrategy, RejectsEmptyCandidates)
{
    const MaxScoreStrategy strategy;

    EXPECT_THROW(strategy.select({}), std::runtime_error);
}

TEST(MaxScoreStrategy, SelectsTheActionWithTheHighestScore)
{
    const MaxScoreStrategy strategy;
    const ActionCandidates candidates{
        {RevealAction{{0, 0}}, 0.2F},
        {ToggleFlagAction{{1, 1}}, 0.9F},
        {RevealNeighborsAction{{2, 2}}, 0.5F}
    };

    const auto action = strategy.select(candidates);

    ASSERT_TRUE(std::holds_alternative<ToggleFlagAction>(action));
    EXPECT_EQ(std::get<ToggleFlagAction>(action).position, Position({1, 1}));
}

TEST(MaxScoreStrategy, KeepsTheFirstActionWhenScoresAreEqual)
{
    const MaxScoreStrategy strategy;
    const ActionCandidates candidates{
        {RevealAction{{0, 0}}, 0.9F},
        {ToggleFlagAction{{1, 1}}, 0.9F}
    };

    const auto action = strategy.select(candidates);

    ASSERT_TRUE(std::holds_alternative<RevealAction>(action));
    EXPECT_EQ(std::get<RevealAction>(action).position, Position({0, 0}));
}

} // namespace
