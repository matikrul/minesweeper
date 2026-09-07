#pragma once

#include <vector>

#include <engine/CellView.hpp>
#include <engine/Position.hpp>

namespace minesweeper {

// forward declaration
class Board;

class BoardView
{
public:
    explicit BoardView(const Board& board);

    int width() const noexcept;
    int height() const noexcept;

    const CellView& cell_at(Position position) const;
    std::vector<Position> get_neighbors(Position position) const;

private:
    int _width;
    int _height;
    std::vector<CellView> _cells;
};

} // namespace minesweeper