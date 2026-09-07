#include <vector>
#include <stdexcept>

#include <ai/encoding/BoardEncoder.hpp>

namespace minesweeper {

namespace {

enum class EncodedCell : int
{
    hidden = -1,
    flagged = -2
};

} // namespace

std::vector<float> BoardEncoder::encode(const BoardView& board) const
{
    const auto cell_count = static_cast<std::size_t>(board.width()) * static_cast<std::size_t>(board.height());
    std::vector<float> board_encoded(cell_count);

    for (int row = 0; row < board.height(); ++row)
    {
        for (int column = 0; column < board.width(); ++column)
        {
            const auto vector_idx = static_cast<std::size_t>(row) * static_cast<std::size_t>(board.width()) +
                                    static_cast<std::size_t>(column);
            const auto& cell = board.cell_at({row, column});

            switch (cell.state)
            {
                case CellViewState::hidden:
                    board_encoded[vector_idx] = static_cast<float>(EncodedCell::hidden);
                    break;
                case CellViewState::flagged:
                    board_encoded[vector_idx] = static_cast<float>(EncodedCell::flagged);
                    break;
                case CellViewState::revealed:
                    if (cell.has_mine)
                        throw std::logic_error("Cannot encode a revealed mine.");
                    else
                        board_encoded[vector_idx] = static_cast<float>(cell.adjacent_mines);
                    break;
                default:
                    throw(std::invalid_argument("Unrecognized CellView state."));
                    break;
            }
        }
    }

    return board_encoded;
}

} // namespace minesweeper