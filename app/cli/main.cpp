#include <iostream>

#include <Game.hpp>

int main()
{
    minesweeper::Game game(5, 5, 5);

    while (true)
    {
        std::cout << "\n";
        game.board().print_board();

        std::cout << "\n";
        std::cout << "1 - Reveal\n";
        std::cout << "2 - Toggle flag\n";
        std::cout << "3 - Reveal neighbors\n";
        std::cout << "Choose action: ";

        int action_type;
        std::cin >> action_type;

        if (!std::cin)
            break;

        int row;
        int column;

        std::cout << "Enter position (row column): ";
        std::cin >> row >> column;

        if (!std::cin)
            break;

        minesweeper::Action action;

        switch (action_type)
        {
            case 1:
                action = minesweeper::RevealAction{{row, column}};
                break;

            case 2:
                action = minesweeper::ToggleFlagAction{{row, column}};
                break;

            case 3:
                action = minesweeper::RevealNeighborsAction{{row, column}};
                break;

            default:
                std::cout << "Unknown action.\n";
                continue;
        }

        try
        {
            const auto state = game.make_action(action);

            if (state == minesweeper::GameState::won)
            {
                game.board().print_board();
                std::cout << "\nYou won!\n";
                break;
            }

            if (state == minesweeper::GameState::lost)
            {
                game.board().print_board();
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