#include <stdexcept>
#include <variant>
#include <vector>

#include <gtest/gtest.h>

#include <ai/decision/ActionsPerCell.hpp>

using namespace minesweeper;

namespace {

TEST(ActionsPerCell, RejectsEmptyActionCoding)
{
    EXPECT_THROW(ActionsPerCell({}), std::invalid_argument);
}

TEST(ActionsPerCell, CreatesCandidatesForEveryCellAndConfiguredAction)
{
    const ActionsPerCell interpreter({ActionCode::reveal, ActionCode::flag});
    const ModelOutput output{
        3,
        2,
        {0.1F, 0.2F, 0.3F, 0.4F, 0.5F, 0.6F,
         0.7F, 0.8F, 0.9F, 1.0F, 1.1F, 1.2F}
    };

    const auto candidates = interpreter.interpret(output);

    ASSERT_EQ(candidates.size(), 12U);
    ASSERT_TRUE(std::holds_alternative<RevealAction>(candidates[0].action));
    EXPECT_EQ(std::get<RevealAction>(candidates[0].action).position, Position({0, 0}));
    EXPECT_FLOAT_EQ(candidates[0].score, 0.1F);
    ASSERT_TRUE(std::holds_alternative<ToggleFlagAction>(candidates[1].action));
    EXPECT_EQ(std::get<ToggleFlagAction>(candidates[1].action).position, Position({0, 0}));
    EXPECT_FLOAT_EQ(candidates[1].score, 0.2F);
    ASSERT_TRUE(std::holds_alternative<RevealAction>(candidates[6].action));
    EXPECT_EQ(std::get<RevealAction>(candidates[6].action).position, Position({1, 0}));
    EXPECT_FLOAT_EQ(candidates[6].score, 0.7F);
    ASSERT_TRUE(std::holds_alternative<ToggleFlagAction>(candidates[11].action));
    EXPECT_EQ(std::get<ToggleFlagAction>(candidates[11].action).position, Position({1, 2}));
    EXPECT_FLOAT_EQ(candidates[11].score, 1.2F);
}

TEST(ActionsPerCell, SupportsAllActionCodes)
{
    const ActionsPerCell interpreter(
        {ActionCode::reveal, ActionCode::flag, ActionCode::reveal_neighbors});
    const ModelOutput output{1, 1, {0.1F, 0.2F, 0.3F}};

    const auto candidates = interpreter.interpret(output);

    ASSERT_EQ(candidates.size(), 3U);
    ASSERT_TRUE(std::holds_alternative<RevealAction>(candidates[0].action));
    EXPECT_EQ(std::get<RevealAction>(candidates[0].action).position, Position({0, 0}));
    ASSERT_TRUE(std::holds_alternative<ToggleFlagAction>(candidates[1].action));
    EXPECT_EQ(std::get<ToggleFlagAction>(candidates[1].action).position, Position({0, 0}));
    ASSERT_TRUE(std::holds_alternative<RevealNeighborsAction>(candidates[2].action));
    EXPECT_EQ(std::get<RevealNeighborsAction>(candidates[2].action).position, Position({0, 0}));
}

TEST(ActionsPerCell, RejectsOutputWithUnexpectedScoreCount)
{
    const ActionsPerCell interpreter({ActionCode::reveal, ActionCode::flag});
    const ModelOutput output{2, 2, {0.1F, 0.2F, 0.3F}};

    EXPECT_THROW(interpreter.interpret(output), std::runtime_error);
}

TEST(ActionsPerCell, RejectsUnsupportedActionCode)
{
    const ActionsPerCell interpreter({static_cast<ActionCode>(99)});
    const ModelOutput output{1, 1, {0.1F}};

    EXPECT_THROW(interpreter.interpret(output), std::runtime_error);
}

} // namespace
