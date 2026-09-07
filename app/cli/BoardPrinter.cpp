#include <BoardPrinter.hpp>

#include <iostream>

namespace minesweeper {

void BoardPrinter::print(const BoardView& board_view)
{
    for (int row = 0; row < board_view.height(); ++row)
    {
        for (int column = 0; column < board_view.width(); ++column)
        {
            const auto& cell = board_view.cell_at({row, column});

            switch (cell.state)
            {
                case CellViewState::hidden:
                    std::cout << ". ";
                    break;

                case CellViewState::flagged:
                    std::cout << "F ";
                    break;

                case CellViewState::revealed:
                    if (cell.has_mine)
                        std::cout << "* ";
                    else if (cell.adjacent_mines == 0)
                        std::cout << "_ ";
                    else
                        std::cout << static_cast<int>(cell.adjacent_mines) << ' ';
                    break;
            }
        }

        std::cout << '\n';
    }
}

} // namespace minesweeper