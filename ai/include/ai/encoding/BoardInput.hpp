#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

#include <engine/Position.hpp>

namespace minesweeper {

/**
 * @brief Numerical board input ready to be passed to an AI model adapter.
 *
 * Values are stored in one contiguous row-major buffer for efficient model
 * inference. `value_at()` and `set_value()` expose the buffer as a 2D board
 * and centralize its index calculation.
 */
struct BoardInput
{
    int width;
    int height;
    std::vector<float> values;

    /**
     * @brief Returns the value for a board position.
     * @throws std::out_of_range If the position is outside the input shape.
     */
    float value_at(Position position) const
    {
        return values.at(index_of(position));
    }

    /**
     * @brief Replaces the value for a board position.
     * @throws std::out_of_range If the position is outside the input shape.
     */
    void set_value(Position position, float value)
    {
        values.at(index_of(position)) = value;
    }

private:
    std::size_t index_of(Position position) const
    {
        if (position.row < 0 || position.row >= height ||
            position.column < 0 || position.column >= width)
        {
            throw std::out_of_range("Board input position is outside its shape.");
        }

        return static_cast<std::size_t>(position.row) * static_cast<std::size_t>(width) +
               static_cast<std::size_t>(position.column);
    }
};

} // namespace minesweeper
