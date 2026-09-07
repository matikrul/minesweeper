#include <iostream>

#include <engine/Game.hpp>
#include <BoardPrinter.hpp>

int main()
{
    minesweeper::Game game(5, 5, 5);

    while (true)
    {
        std::cout << "\n";
        minesweeper::BoardPrinter::print(game.board_view());

        std::cout << "\n";
        std::cout << "1/r - Reveal\n";
        std::cout << "2/f - Toggle flag\n";
        std::cout << "3/n - Reveal neighbors\n";
        std::cout << "Choose action: ";

        char action_type;
        std::cin >> action_type;

        if (!std::cin)
            break;

        int row;
        int column;

        std::cout << "Enter position (row column - counting from 1 1): ";
        std::cin >> row >> column;

        if (!std::cin)
            break;

        minesweeper::Action action;

        switch (action_type)
        {
            case 1:
            case 'r':
            case 'R':
                action = minesweeper::RevealAction{{row - 1, column - 1}};
                break;

            case 2:
            case 'f':
            case 'F':
                action = minesweeper::ToggleFlagAction{{row - 1, column - 1}};
                break;

            case 3:
            case 'n':
            case 'N':
                action = minesweeper::RevealNeighborsAction{{row - 1, column - 1}};
                break;

            default:
                std::cout << "Unknown action.\n";
                continue;
        }

        try
        {
            const auto state = game.make_action(action);

            std::cout << "\nGame state is: ";
            switch (state)
            {
                case minesweeper::GameState::won:
                    std::cout << "won\n";
                    break;
                case minesweeper::GameState::lost:
                    std::cout << "lost\n";
                    break;
                case minesweeper::GameState::in_progress:
                    std::cout << "in progress\n";
                    break;
            }

            if (state == minesweeper::GameState::won)
            {
                minesweeper::BoardPrinter::print(game.board_view());
                std::cout << "\nYou won!\n";
                break;
            }

            if (state == minesweeper::GameState::lost)
            {
                minesweeper::BoardPrinter::print(game.board_view());
                std::cout << "\nYou lost!\n";
                break;
            }
        }
        catch (const std::out_of_range& exception)
        {
            std::cout << "Invalid position: "
                      << exception.what() << '\n';
        }
    }

    return 0;
}