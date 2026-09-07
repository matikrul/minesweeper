#pragma once

#include <cstdint>

namespace minesweeper {

enum class CellViewState
{
    hidden,
    flagged,
    revealed
};

struct CellView
{
    CellViewState state{CellViewState::hidden};
    std::uint8_t adjacent_mines{0};
    bool has_mine{false};
};

} // namespace minesweeper