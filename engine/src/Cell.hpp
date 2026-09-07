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

    void set_flag(bool enable) noexcept;
    void set_revealed() noexcept;
    void set_mine() noexcept { _has_mine = true; }
    void set_adjacent_mines(std::uint8_t count) noexcept { _adjacent_mines = count; }

    [[nodiscard]] bool has_mine() const noexcept { return _has_mine; }
    [[nodiscard]] std::uint8_t adjacent_mines() const noexcept { return _adjacent_mines; }
    [[nodiscard]] bool is_revealed() const noexcept { return _state == CellState::revealed; }
    [[nodiscard]] bool is_flagged() const noexcept { return _state == CellState::flagged; }

private:
    bool _has_mine{false};
    std::uint8_t _adjacent_mines{0};
    CellState _state{CellState::hidden};
};

} // namespace minesweeper
