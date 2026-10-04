#include <stdexcept>
#include <vector>

#include <ai/encoding/BoardEncoder.hpp>

namespace minesweeper {

namespace {

enum class EncodedCell : int
{
    hidden = -1,
    flagged = -2
};

} // namespace

BoardInput BoardEncoder::encode(const BoardView& board) const
{
    const auto cell_count = static_cast<std::size_t>(board.width()) * static_cast<std::size_t>(board.height());
    BoardInput board_input{board.width(), board.height(), std::vector<float>(cell_count)};

    for (int row = 0; row < board.height(); ++row)
    {
        for (int column = 0; column < board.width(); ++column)
        {
            const auto& cell = board.cell_at({row, column});

            switch (cell.state)
            {
                case CellViewState::hidden:
                    board_input.set_value({row, column}, static_cast<float>(EncodedCell::hidden));
                    break;
                case CellViewState::flagged:
                    board_input.set_value({row, column}, static_cast<float>(EncodedCell::flagged));
                    break;
                case CellViewState::revealed:
                    if (cell.has_mine)
                        throw std::logic_error("Cannot encode a revealed mine.");
                    else
                        board_input.set_value({row, column}, static_cast<float>(cell.adjacent_mines));
                    break;
                default:
                    throw(std::invalid_argument("Unrecognized CellView state."));
                    break;
            }
        }
    }

    return board_input;
}

} // namespace minesweeper
