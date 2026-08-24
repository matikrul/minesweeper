#include <stdexcept>
#include <algorithm>
#include <random>
#include <iostream>

#include <Board.hpp>

namespace minesweeper {

Board::Board(int width, int height, int mine_count)
    : _width(width),
      _height(height),
      _mine_count(mine_count)
{
    if (width <= 0 || height <= 0)
    throw std::invalid_argument("Board dimensions must be positive.");

    if (mine_count > static_cast<std::size_t>(width * height - 1))
        throw std::invalid_argument("Too many mines.");

    _cells.resize(_width * _height);
}

bool Board::is_valid_position(Position position) const noexcept
{
    return position.row >= 0 && position.row < _height &&
           position.column >= 0 && position.column < _width;
}

const Cell& Board::cell_at(Position position) const
{
    if (!is_valid_position(position))
        throw std::out_of_range("Requesting cell at non existing position.");
    return _cells[position.row * _width + position.column];
}

std::vector<Position> Board::get_neighbors(Position position) const
{
    if (!is_valid_position(position))
        throw std::out_of_range("Requesting neighbors for non existing position.");

    std::vector<Position> neighbors;

    for (int row_offset = -1; row_offset <= 1; ++row_offset)
    {
        for (int column_offset = -1; column_offset <= 1; ++column_offset)
        {
            if (row_offset == 0 && column_offset == 0)
                continue;

            Position neighbour{
                position.row + row_offset,
                position.column + column_offset
            };

            if (is_valid_position(neighbour))
                neighbors.push_back(neighbour);
        }
    }

    return neighbors;
}

void Board::place_mines(Position safe_position)
{
    if (!is_valid_position(safe_position))
        throw std::out_of_range("Safe position is outside the board.");

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(0, _width * _height - 1);
    std::size_t mines_placed = 0;

    while (mines_placed < _mine_count)
    {
        const auto index = distribution(generator);
        const Position position{
            index / _width,
            index % _width
        };

        if (position == safe_position)
            continue;

        if (_cells[index].has_mine())
            continue;

        _cells[index].set_mine();
        ++mines_placed;
    }
}

void Board::reveal(Position position)
{

}

void Board::toggle_flag(Position position)
{
    auto& cell = _cells[position.row * _width + position.column];
    cell.set_flag(true);
}

void Board::print_board() const
{
    for (int row = 0; row < _height; ++row)
    {
        for (int column = 0; column < _width; ++column)
        {
            const auto& cell = cell_at({row, column});
            if (cell.has_mine())
                std::cout << "* ";
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
} // namespace minesweeper