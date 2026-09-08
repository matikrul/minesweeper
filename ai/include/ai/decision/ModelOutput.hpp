#pragma once

#include <vector>

namespace minesweeper {

struct ModelOutput
{
    int board_width;
    int board_height;
    std::vector<float> scores;
};

} // namespace minesweeper