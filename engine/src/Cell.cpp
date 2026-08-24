#include <Cell.hpp>

namespace minesweeper {

void Cell::set_flag(bool enable) noexcept
{
    if (_state == CellState::revealed)
        return;

    if (enable)
        _state = CellState::flagged;
    else
        _state = CellState::hidden;
}

void Cell::set_revealed() noexcept
{
    if (_state != CellState::flagged)
        _state = CellState::revealed;
}
}