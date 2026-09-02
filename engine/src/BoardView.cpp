#include <BoardView.hpp>

#include <stdexcept>

#include <Board.hpp>

namespace minesweeper {

BoardView::BoardView(const Board& board)
    : _width(board.width()),
      _height(board.height()),
      _cells(static_cast<std::size_t>(_width) *
             static_cast<std::size_t>(_height))
{
    for (int row = 0; row < _height; ++row)
    {
        for (int column = 0; column < _width; ++column)
        {
            const Position position{row, column};
            const auto& cell = board.cell_at(position);

            auto& view = _cells[
                static_cast<std::size_t>(row) *
                static_cast<std::size_t>(_width) +
                static_cast<std::size_t>(column)
            ];

            if (cell.is_flagged())
            {
                view.state = CellViewState::flagged;
                view.adjacent_mines = 0;
            }
            else if (cell.is_revealed())
            {
                view.state = CellViewState::revealed;
                view.adjacent_mines = cell.adjacent_mines();
            }
            else
            {
                view.state = CellViewState::hidden;
                view.adjacent_mines = 0;
            }
        }
    }
}

int BoardView::width() const noexcept
{
    return _width;
}

int BoardView::height() const noexcept
{
    return _height;
}

const CellView& BoardView::cell_at(Position position) const
{
    if (position.row < 0 || position.row >= _height ||
        position.column < 0 || position.column >= _width)
    {
        throw std::out_of_range(
            "Requesting cell at non existing position.");
    }

    return _cells[
        static_cast<std::size_t>(position.row) *
        static_cast<std::size_t>(_width) +
        static_cast<std::size_t>(position.column)
    ];
}

} // namespace minesweeper