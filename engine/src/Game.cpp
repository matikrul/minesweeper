#include <algorithm>

#include <Game.hpp>

namespace minesweeper {

Game::Game(int width, int height, int mine_count)
    : _board(width, height, mine_count)
{
}

GameState Game::make_action(const Action& action)
{
    std::visit(
        [this](const auto& action)
        {
            execute(action);
        },
        action);

    if (is_won())
        _state = GameState::won;

    return _state;
}

void Game::execute(const RevealAction& action)
{
    _board.reveal(action.position);

    if (_board.cell_at(action.position).has_mine())
    {
        _state = GameState::lost;
        return;
    }
}

void Game::execute(const ToggleFlagAction& action)
{
    _board.toggle_flag(action.position);
}

void Game::execute(const RevealNeighborsAction& action)
{
    const auto& cell = _board.cell_at(action.position);

    if (!cell.is_revealed())
        return;

    auto neighbors = _board.get_neighbors(action.position);

    const auto flagged_neighbors = std::count_if(
        neighbors.begin(),
        neighbors.end(),
        [this](Position neighbor) {
            return _board.cell_at(neighbor).is_flagged();
        });

    if (flagged_neighbors != cell.adjacent_mines())
        return;

    for (const auto &pos : neighbors)
    {
        if (_board.cell_at(pos).is_flagged())
            continue;

        _board.reveal(pos);

        if (_board.cell_at(pos).has_mine())
        {
            _state = GameState::lost;
            return;
        }
    }
}

bool Game::is_won() const
{
    for (int row = 0; row < _board.height(); ++row)
    {
        for (int column = 0; column < _board.width(); ++column)
        {
            const auto& cell = _board.cell_at({row, column});

            if (!cell.has_mine() && !cell.is_revealed())
                return false;
        }
    }

    return true;
}

const Board& Game::board() const noexcept
{
    return _board;
}

BoardView Game::board_view() const
{
    return BoardView(_board);
}

} // namespace minesweeper