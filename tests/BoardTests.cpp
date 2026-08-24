#include <iostream>
#include <stdexcept>

#include <Board.hpp>

namespace {

int failures = 0;

void expect(bool condition, const char* message)
{
    if (!condition)
    {
        std::cerr << "FAIL: " << message << '\n';
        ++failures;
    }
}

template <typename Function>
void expect_throws(Function&& function, const char* message)
{
    bool threw = false;
    try
    {
        function();
    }
    catch (...)
    {
        threw = true;
    }

    expect(threw, message);
}

} // namespace

int main()
{
    using minesweeper::Board;
    using minesweeper::Position;

    {
        Board board(3, 3, 1);
        expect(board.width() == 3, "width is stored");
        expect(board.height() == 3, "height is stored");
        expect(board.mine_count() == 1, "mine count is stored");
        expect(board.is_valid_position({0, 0}), "origin is valid");
        expect(!board.is_valid_position({-1, 0}), "negative row is invalid");
        expect_throws([] { Board invalid_board(0, 1, 0); }, "zero width is rejected");
        expect_throws([] { Board invalid_board(1, 1, 2); }, "too many mines are rejected");
    }

    {
        Board board(3, 3, 1);
        expect_throws([&board] { board.toggle_flag({-1, 0}); }, "flagging outside the board throws");

        board.toggle_flag({1, 1});
        expect(board.cell_at({1, 1}).is_flagged(), "toggle_flag sets a flag");

        board.toggle_flag({1, 1});
        expect(!board.cell_at({1, 1}).is_flagged(), "toggle_flag removes a flag");
    }

    {
        Board board(4, 4, 2);
        board.reveal({0, 0});

        int mine_cells = 0;
        for (int row = 0; row < board.height(); ++row)
        {
            for (int column = 0; column < board.width(); ++column)
            {
                const auto position = Position{row, column};
                if (board.cell_at(position).has_mine())
                    ++mine_cells;
            }
        }

        expect(mine_cells == 2, "mine placement matches the configured count");
        expect(!board.cell_at({0, 0}).has_mine(), "safe position is not mined");
        expect(board.cell_at({0, 0}).is_revealed(), "first reveal reveals the chosen cell");
    }

    {
        Board board(2, 2, 1);
        board.reveal({0, 0});
        expect_throws([&board] { board.place_mines({0, 1}); }, "placing mines twice is rejected");
    }

    if (failures != 0)
        return 1;

    std::cout << "All tests passed\n";
    return 0;
}
