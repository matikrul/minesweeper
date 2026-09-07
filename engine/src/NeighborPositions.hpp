#pragma once

#include <stdexcept>
#include <vector>

#include <engine/Position.hpp>

namespace minesweeper {

inline std::vector<Position> neighbor_positions(
    int width,
    int height,
    Position position)
{
    if (position.row < 0 || position.row >= height ||
        position.column < 0 || position.column >= width)
    {
        throw std::out_of_range("Requesting neighbors for non existing position.");
    }

    std::vector<Position> neighbors;

    for (int row_offset = -1; row_offset <= 1; ++row_offset)
    {
        for (int column_offset = -1; column_offset <= 1; ++column_offset)
        {
            if (row_offset == 0 && column_offset == 0)
                continue;

            const Position neighbor{
                position.row + row_offset,
                position.column + column_offset};

            if (neighbor.row >= 0 && neighbor.row < height &&
                neighbor.column >= 0 && neighbor.column < width)
            {
                neighbors.push_back(neighbor);
            }
        }
    }

    return neighbors;
}

} // namespace minesweeper::detail
