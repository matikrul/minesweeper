#pragma once

#include <cstddef>
#include <vector>

#include "Cell.hpp"
#include "Position.hpp"

namespace minesweeper {

class Board {
public:
    Board(int width, int height, int mine_count);
    [[nodiscard]] int width() const noexcept { return _width; }
    [[nodiscard]] int height() const noexcept { return _height; }
    [[nodiscard]] int mine_count() const noexcept { return _mine_count; }

    [[nodiscard]] bool is_valid_position(Position position) const noexcept;
    [[nodiscard]] const Cell& cell_at(Position position) const;
    [[nodiscard]] std::vector<Position> get_neighbors(Position position) const;

    void place_mines(Position safe_position);
    void reveal(Position position);
    void toggle_flag(Position position);
    void print_board() const;

private:
    int _width{};
    int _height{};
    int _mine_count{};
    std::vector<Cell> _cells{};
};

} // namespace minesweeper
