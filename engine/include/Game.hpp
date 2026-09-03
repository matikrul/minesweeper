#pragma once

#include <Board.hpp>
#include <BoardView.hpp>
#include <Action.hpp>

namespace minesweeper {

enum class GameState
{
    in_progress,
    won,
    lost
};

class Game
{
public:
    Game(int width, int height, int mine_count);

    static Game from_mines(int width, int height, const std::vector<Position>& mines);

    GameState make_action(const Action& action);

    BoardView board_view() const;

    const Board& board() const noexcept;

private:
    explicit Game(Board board);

    void execute(const RevealAction& action);
    void execute(const ToggleFlagAction& action);
    void execute(const RevealNeighborsAction& action);

    bool is_won() const;

    Board _board;
    GameState _state{GameState::in_progress};
};

} // namespace minesweeper