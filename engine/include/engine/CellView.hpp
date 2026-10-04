#pragma once

#include <cstdint>

namespace minesweeper {

/** @brief State of a cell visible to a client. */
enum class CellViewState
{
    hidden,
    flagged,
    revealed
};

/**
 * @brief Public cell representation that does not reveal hidden mines.
 *
 * For hidden and flagged cells, `adjacent_mines` is 0 and `has_mine` is
 * false. Mine and adjacent-mine information is available only for a
 * revealed cell.
 */
struct CellView
{
    CellViewState state{CellViewState::hidden};
    std::uint8_t adjacent_mines{0};
    bool has_mine{false};
};

} // namespace minesweeper
