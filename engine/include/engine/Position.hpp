#pragma once

namespace minesweeper {

struct Position {
    int row{};
    int column{};

    [[nodiscard]] constexpr bool operator==(const Position&) const noexcept = default;
};

} // namespace minesweeper
