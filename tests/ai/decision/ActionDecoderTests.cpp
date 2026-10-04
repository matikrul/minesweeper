#include <memory>
#include <variant>
#include <vector>

#include <gtest/gtest.h>

#include <ai/decision/ActionDecoder.hpp>
#include <ai/decision/ActionsPerCell.hpp>
#include <ai/decision/MaxScoreStrategy.hpp>

using namespace minesweeper;

namespace {

TEST(ActionDecoder, InterpretsAndSelectsTheBestModelAction)
{
    ActionDecoder decoder(
        std::make_unique<ActionsPerCell>(
            std::vector<ActionCode>{ActionCode::reveal, ActionCode::flag}),
        std::make_unique<MaxScoreStrategy>());
    const ModelOutput output{2, 1, 2, {0.2F, 0.4F, 0.9F, 0.1F}};

    const auto action = decoder.decode(output);

    ASSERT_TRUE(std::holds_alternative<RevealAction>(action));
    EXPECT_EQ(std::get<RevealAction>(action).position, Position({0, 1}));
}

} // namespace
