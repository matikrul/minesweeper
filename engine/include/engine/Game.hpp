#pragma once

#include <memory>
#include <vector>

#include <engine/BoardView.hpp>
#include <engine/Action.hpp>

namespace minesweeper {

enum class GameState
{
    in_progress,
    won,
    lost
};

// forward declaration
class Board;

class Game
{
public:
    Game(int width, int height, int mine_count);
    ~Game();

    static Game from_mines(int width, int height, const std::vector<Position>& mines);

    GameState make_action(const Action& action);

    BoardView board_view() const;

private:
    explicit Game(std::unique_ptr<Board> board);

    void execute(const RevealAction& action);
    void execute(const ToggleFlagAction& action);
    void execute(const RevealNeighborsAction& action);

    bool is_won() const;

    std::unique_ptr<Board> _board;
    GameState _state{GameState::in_progress};
};

} // namespace minesweeper
