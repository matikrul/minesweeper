#pragma once

#include <vector>

namespace minesweeper {

/**
 * @brief Raw AI model output for one board.
 *
 * `scores` does not itself define positions or move kinds. An
 * `IActionInterpreter` implementation, such as `ActionsPerCell`, provides
 * that meaning. Height and width let the interpreter reconstruct positions.
 */
struct ModelOutput
{
    int board_width;
    int board_height;
    std::vector<float> scores;
};

} // namespace minesweeper
