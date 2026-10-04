#pragma once

#include <variant>

#include <engine/Position.hpp>

namespace minesweeper {

/** @brief Reveals the cell at `position`. */
struct RevealAction
{
    Position position;
};

/** @brief Adds or removes a flag at `position`. */
struct ToggleFlagAction
{
    Position position;
};

/**
 * @brief Attempts to reveal the neighbors of an already revealed cell.
 *
 * The move takes effect only when the number of neighboring flags matches
 * the adjacent mine count shown by the cell.
 */
struct RevealNeighborsAction
{
    Position position;
};

/** @brief Any move accepted by `Game::make_action()`. */
using Action = std::variant<
    RevealAction,
    ToggleFlagAction,
    RevealNeighborsAction
>;

/**
 * @brief Action kind code used in AI model output.
 *
 * The code order passed to `ActionsPerCell` determines the order of model
 * scores for each cell; the enum values themselves do not impose that order.
 */
enum class ActionCode : int
{
    reveal = 0,
    flag = 1,
    reveal_neighbors = 2
};

} // namespace minesweeper
