#pragma once

#include <memory>
#include <vector>

#include <engine/BoardView.hpp>
#include <engine/Action.hpp>

namespace minesweeper {

/** @brief Game result after executing a move. */
enum class GameState
{
    in_progress,
    won,
    lost
};

// forward declaration
class Board;

/**
 * @brief Facade for the Minesweeper game engine.
 *
 * Manages the hidden board, executes moves, and tracks win or loss. Clients
 * can inspect state only through `BoardView`.
 */
class Game
{
public:
    /**
     * @brief Creates a game whose mines are placed on the first reveal.
     * The first revealed cell is never a mine.
     */
    Game(int width, int height, int mine_count);
    ~Game();

    /**
     * @brief Creates a game with a fixed mine layout.
     *
     * Useful for tests and deterministic scenarios.
     */
    static Game from_mines(int width, int height, const std::vector<Position>& mines);

    /** @brief Executes a move and returns the resulting game state. */
    GameState make_action(const Action& action);

    /** @brief Returns a board snapshot without exposing hidden mines. */
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
