#include <gtest/gtest.h>

#include <Cell.hpp>

using namespace minesweeper;

TEST(CellState, IsHiddenByDefault)
{
    Cell cell;

    EXPECT_FALSE(cell.is_revealed());
    EXPECT_FALSE(cell.is_flagged());
}

TEST(CellState, DoesNotHaveMineByDefault)
{
    Cell cell;

    EXPECT_FALSE(cell.has_mine());
}

TEST(CellState, HasNoAdjacentMinesByDefault)
{
    Cell cell;

    EXPECT_EQ(cell.adjacent_mines(), 0);
}

TEST(CellMine, SetMineMarksCellAsMine)
{
    Cell cell;

    cell.set_mine();

    EXPECT_TRUE(cell.has_mine());
}

TEST(CellAdjacentMines, SetAdjacentMinesStoresCount)
{
    Cell cell;

    cell.set_adjacent_mines(5);

    EXPECT_EQ(cell.adjacent_mines(), 5);
}

TEST(CellReveal, SetRevealedRevealsCell)
{
    Cell cell;

    cell.set_revealed();

    EXPECT_TRUE(cell.is_revealed());
    EXPECT_FALSE(cell.is_flagged());
}

TEST(CellReveal, RevealedCellCannotBeFlagged)
{
    Cell cell;

    cell.set_revealed();
    cell.set_flag(true);

    EXPECT_TRUE(cell.is_revealed());
    EXPECT_FALSE(cell.is_flagged());
}

TEST(CellFlag, SetFlagFlagsHiddenCell)
{
    Cell cell;

    cell.set_flag(true);

    EXPECT_TRUE(cell.is_flagged());
    EXPECT_FALSE(cell.is_revealed());
}

TEST(CellFlag, SetFlagFalseUnflagsCell)
{
    Cell cell;

    cell.set_flag(true);
    cell.set_flag(false);

    EXPECT_FALSE(cell.is_flagged());
    EXPECT_FALSE(cell.is_revealed());
}

TEST(CellFlag, FlaggedCellCannotBeRevealed)
{
    Cell cell;

    cell.set_flag(true);
    cell.set_revealed();

    EXPECT_TRUE(cell.is_flagged());
    EXPECT_FALSE(cell.is_revealed());
}