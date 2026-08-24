#pragma once

#include <cstdint>

namespace minesweeper {

class Cell {
public:
    enum class CellState {
        hidden,
        revealed,
        flagged,
    };


    void set_flag(bool enable);
    void set_mine() { _has_mine = true; };
    bool has_mine() const { return _has_mine; };

private:
    bool _has_mine{false};
    std::uint8_t _adjacent_mines{0};
    CellState _state{CellState::hidden};
};

} // namespace minesweeper
