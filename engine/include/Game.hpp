#pragma once

#include <Board.hpp>
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

    GameState make_action(const Action& action);

    const Board& board() const noexcept;

private:
    void execute(const RevealAction& action);
    void execute(const ToggleFlagAction& action);
    void execute(const RevealNeighborsAction& action);

    bool is_won() const;

    Board _board;
    GameState _state{GameState::in_progress};
};

} // namespace minesweeper