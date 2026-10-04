#pragma once

#include <vector>

#include <engine/CellView.hpp>
#include <engine/Position.hpp>

namespace minesweeper {

class Board;
class Game;

/**
 * @brief Immutable snapshot of the current board state.
 */
class BoardView
{
public:
    /** @brief Number of board columns. */
    int width() const noexcept;
    /** @brief Number of board rows. */
    int height() const noexcept;

    /**
     * @brief Returns the view of the cell at the given position.
     * @throws std::out_of_range If the position is outside the board.
     */
    const CellView& cell_at(Position position) const;
    /**
     * @brief Returns up to eight adjacent positions.
     * @throws std::out_of_range If the position is outside the board.
     */
    std::vector<Position> get_neighbors(Position position) const;

private:
    friend class Game;

    explicit BoardView(const Board& board);

    int _width;
    int _height;
    std::vector<CellView> _cells;
};

} // namespace minesweeper
