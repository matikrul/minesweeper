#pragma once

#include <vector>

#include <CellView.hpp>
#include <Position.hpp>

namespace minesweeper {

class Board;

class BoardView
{
public:
    explicit BoardView(const Board& board);

    int width() const noexcept;
    int height() const noexcept;

    const CellView& cell_at(Position position) const;

private:
    int _width;
    int _height;
    std::vector<CellView> _cells;
};

} // namespace minesweeper