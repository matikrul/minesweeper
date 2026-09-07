#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include <Board.hpp>
#include <NeighborPositions.hpp>

namespace minesweeper {
namespace {

std::uint8_t count_adjacent_mines(const Board& board, Position position)
{
    const auto neighbors = board.get_neighbors(position);
    const auto mine_count = std::count_if(
        neighbors.begin(),
        neighbors.end(),
        [&board](Position neighbor) {
            return board.cell_at(neighbor).has_mine();
        });

    return static_cast<std::uint8_t>(mine_count);
}

std::size_t cell_index(int width, Position position) noexcept
{
    return static_cast<std::size_t>(position.row) * static_cast<std::size_t>(width) +
           static_cast<std::size_t>(position.column);
}

} // namespace

Board::Board(int width, int height, int mine_count)
    : _width(width),
      _height(height),
      _mine_count(mine_count)
{
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Board dimensions must be positive.");

    if (mine_count < 0)
        throw std::invalid_argument("Mine count cannot be negative.");

    const auto cell_count = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
    if (static_cast<std::size_t>(mine_count) > cell_count - 1)
        throw std::invalid_argument("Too many mines.");

    _cells.resize(cell_count);
}

Board Board::from_mines(
    int width,
    int height,
    const std::vector<Position>& mines)
{
    Board board(width, height, static_cast<int>(mines.size()));

    for (const auto position : mines)
    {
        if (!board.is_valid_position(position))
            throw std::out_of_range("Mine position is outside the board.");

        auto& cell = board.cell_at(position);

        if (cell.has_mine())
            throw std::invalid_argument("Duplicate mine position.");

        cell.set_mine();
    }

    board.calculate_adjacent_mines();
    board._mines_placed = true;

    return board;
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

    return _cells[cell_index(_width, position)];
}

Cell& Board::cell_at(Position position)
{
    if (!is_valid_position(position))
        throw std::out_of_range("Requesting cell at non existing position.");

    return _cells[cell_index(_width, position)];
}

std::vector<Position> Board::get_neighbors(Position position) const
{
    return neighbor_positions(_width, _height, position);
}

void Board::place_mines(Position safe_position)
{
    if (_mines_placed)
        throw std::logic_error("Mines have already been placed.");

    if (!is_valid_position(safe_position))
        throw std::out_of_range("Safe position is outside the board.");

    std::random_device random_device;
    std::mt19937 generator(random_device());
    const auto cell_count = static_cast<std::size_t>(_width) * static_cast<std::size_t>(_height);
    std::uniform_int_distribution<std::size_t> distribution(0, cell_count - 1);
    std::size_t mines_placed = 0;

    while (mines_placed < static_cast<std::size_t>(_mine_count))
    {
        const auto index = distribution(generator);
        const auto width = static_cast<std::size_t>(_width);
        const Position position{
            static_cast<int>(index / width),
            static_cast<int>(index % width)
        };

        if (position == safe_position)
            continue;

        if (_cells[index].has_mine())
            continue;

        _cells[index].set_mine();
        ++mines_placed;
    }

    calculate_adjacent_mines();
    _mines_placed = true;
}

void Board::reveal(Position position)
{
    if (!is_valid_position(position))
        throw std::out_of_range("Requesting reveal for non existing position.");

    if (!_mines_placed)
        place_mines(position);

    std::vector<Position> stack{position};

    while (!stack.empty())
    {
        const auto current = stack.back();
        stack.pop_back();

        auto& cell = cell_at(current);
        if (cell.is_revealed() || cell.is_flagged())
            continue;

        cell.set_revealed();

        if (cell.has_mine() || cell.adjacent_mines() != 0)
            continue;

        for (const auto neighbor : get_neighbors(current))
        {
            const auto& neighbor_cell = cell_at(neighbor);
            if (!neighbor_cell.is_revealed() && !neighbor_cell.is_flagged() && !neighbor_cell.has_mine())
                stack.push_back(neighbor);
        }
    }
}

void Board::toggle_flag(Position position)
{
    if (!is_valid_position(position))
        throw std::out_of_range("Requesting flag toggle for non existing position.");

    auto& cell = cell_at(position);
    if (cell.is_revealed())
        return;

    cell.set_flag(!cell.is_flagged());
}

void Board::calculate_adjacent_mines()
{
    for (int row = 0; row < _height; ++row)
    {
        for (int column = 0; column < _width; ++column)
        {
            const Position position{row, column};

            cell_at(position).set_adjacent_mines(
                count_adjacent_mines(*this, position));
        }
    }
}
} // namespace minesweeper
