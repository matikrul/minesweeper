#pragma once

#include <cstdint>

namespace minesweeper {

enum class CellViewState
{
    hidden,
    revealed,
    flagged
};

struct CellView
{
    CellViewState state;
    std::uint8_t adjacent_mines;
};

} // namespace minesweeper