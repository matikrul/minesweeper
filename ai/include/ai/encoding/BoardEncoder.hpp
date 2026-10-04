#pragma once

#include <vector>

#include <engine/BoardView.hpp>

namespace minesweeper {

/**
 * @brief Converts a `BoardView` into numerical input for an AI model.
 *
 * The result contains `width * height` floats in row-major order: index
 * `row * width + column` represents `Position{row, column}`. A hidden cell
 * is encoded as -1, a flag as -2, and a revealed non-mine as its adjacent
 * mine count (0--8). A revealed mine cannot be encoded and throws a logic
 * error because it is a terminal game state.
 */
class BoardEncoder
{
public:
    /** @throws std::logic_error If the board contains a revealed mine. */
    std::vector<float> encode(const BoardView& board) const;
};

} // namespace minesweeper
