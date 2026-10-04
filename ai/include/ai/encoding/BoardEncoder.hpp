#pragma once

#include <ai/encoding/BoardInput.hpp>
#include <engine/BoardView.hpp>

namespace minesweeper {

/**
 * @brief Converts a `BoardView` into numerical input for an AI model.
 *
 * The result retains the board dimensions and stores values in row-major
 * order. A hidden cell is encoded as -1, a flag as -2, and a revealed
 * non-mine as its adjacent mine count (0--8). A revealed mine cannot be
 * encoded and throws a logic error because it is a terminal game state.
 */
class BoardEncoder
{
public:
    /** @throws std::logic_error If the board contains a revealed mine. */
    BoardInput encode(const BoardView& board) const;
};

} // namespace minesweeper
