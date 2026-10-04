#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

#include <engine/Position.hpp>

namespace minesweeper {

/**
 * @brief Raw AI model output for one board.
 *
 * `scores` does not itself define positions or move kinds. An
 * `IActionInterpreter` implementation, such as `ActionsPerCell`, provides
 * that meaning. The dimensions make the tensor shape explicit, while
 * `score_at()` centralizes row-major index calculation.
 */
struct ModelOutput
{
    int board_width;
    int board_height;
    int actions_per_cell;
    std::vector<float> scores;

    /**
     * @brief Returns the score for one action at one board position.
     * @throws std::out_of_range If the position or action index is invalid.
     */
    float score_at(Position position, int action_index) const
    {
        if (position.row < 0 || position.row >= board_height ||
            position.column < 0 || position.column >= board_width ||
            action_index < 0 || action_index >= actions_per_cell)
        {
            throw std::out_of_range("Model output index is outside its shape.");
        }

        const auto cell_index = static_cast<std::size_t>(position.row) *
                                static_cast<std::size_t>(board_width) +
                                static_cast<std::size_t>(position.column);
        const auto score_index = cell_index * static_cast<std::size_t>(actions_per_cell) +
                                 static_cast<std::size_t>(action_index);
        return scores.at(score_index);
    }
};

} // namespace minesweeper
