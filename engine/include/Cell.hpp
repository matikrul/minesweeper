#pragma once

#include <cstdint>

namespace minesweeper {

enum class CellState {
    hidden,
    revealed,
    flagged,
};

struct Cell {
    bool has_mine{false};
    std::uint8_t adjacent_mines{0};
    CellState state{CellState::hidden};
};

} // namespace minesweeper
