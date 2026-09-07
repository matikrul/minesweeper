#pragma once

#include <vector>

#include <BoardView.hpp>

namespace minesweeper {

class BoardEncoder
{
public:
    std::vector<float> encode(const BoardView& board) const;
};

} // namespace minesweeper