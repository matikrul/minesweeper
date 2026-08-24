#include <Cell.hpp>

namespace minesweeper {

void Cell::set_flag(bool enable)
{
    if (_state == CellState::revealed)
        return;

    if (enable)
        _state = CellState::flagged;
    else
        _state = CellState::hidden;
}
}