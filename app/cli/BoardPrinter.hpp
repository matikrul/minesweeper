#pragma once

#include <engine/BoardView.hpp>

namespace minesweeper {

class BoardPrinter
{
public:
    static void print(const BoardView& board_view);
};

} // namespace minesweeper