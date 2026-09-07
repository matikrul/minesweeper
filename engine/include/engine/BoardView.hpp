#pragma once

#include <vector>

#include <engine/CellView.hpp>
#include <engine/Position.hpp>

namespace minesweeper {

class Board;
class Game;

class BoardView
{
public:
    int width() const noexcept;
    int height() const noexcept;

    const CellView& cell_at(Position position) const;
    std::vector<Position> get_neighbors(Position position) const;

private:
    friend class Game;

    explicit BoardView(const Board& board);

    int _width;
    int _height;
    std::vector<CellView> _cells;
};

} // namespace minesweeper
