#pragma once

#include <variant>

#include <engine/Position.hpp>

namespace minesweeper {

struct RevealAction
{
    Position position;
};

struct ToggleFlagAction
{
    Position position;
};

struct RevealNeighborsAction
{
    Position position;
};

using Action = std::variant<
    RevealAction,
    ToggleFlagAction,
    RevealNeighborsAction
>;

enum class ActionCode : int
{
    reveal = 0,
    flag = 1,
    reveal_neighbors = 2
};

} // namespace minesweeper