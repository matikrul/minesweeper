#pragma once

#include "Cell.h"
#include "Position.h"

#include <cstddef>
#include <vector>

namespace minesweeper {

enum class GameState {
    in_progress,
    won,
    lost,
};

class Board {
public:
    Board(int width, int height, std::size_t mine_count);

    [[nodiscard]] int width() const noexcept;
    [[nodiscard]] int height() const noexcept;
    [[nodiscard]] std::size_t mine_count() const noexcept;
    [[nodiscard]] GameState state() const noexcept;

    [[nodiscard]] bool is_valid_position(Position position) const noexcept;
    [[nodiscard]] const Cell& cell_at(Position position) const;

    void place_mines(Position safe_position);
    void reveal(Position position);
    void toggle_flag(Position position);

private:
    int width_{};
    int height_{};
    std::size_t mine_count_{};
    GameState state_{GameState::in_progress};
    std::vector<Cell> cells_{};
};

} // namespace minesweeper
