#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <time.h>
class Board
{
public:
    enum CellState
    {
        EMPTY,
        X,
        O
    };
    Board()
    {
    }
    CellState getCellValue(int row, int column)
    {
        if (row >= 3 || column >= 3 || row < 0 || column < 0)
        {
            printf("Index out of bounds\n");
            return EMPTY;
        }
        int flatStartIndex = (column + row * 3) * 2;
        int output = boardState[16 - flatStartIndex];
        output <<= 1;
        output |= boardState[16 - flatStartIndex + 1];
        return (CellState)output;
    }
    void setCellValue(int row, int column, CellState state)
    {
        if (row >= 3 || column >= 3 || row < 0 || column < 0)
        {
            std::cout << "Index out of bounds\n";
            return;
        }
        int flatStartIndex = (column + row * 3) * 2;
        std::bitset<18> newState;
        if (state == Board::CellState::X)
        {
            newState.set(16 - flatStartIndex + 1, (state & Board::CellState::X));
        }
        else if (state == Board::CellState::O)
        {
            newState.set(16 - flatStartIndex, (state & Board::CellState::O));
        }
        else
        {
            newState.set(16 - flatStartIndex, false);
            newState.set(16 - flatStartIndex + 1, false);
        }
        boardState |= newState;
    }
    void print()
    {
        std::cout << boardState << '\n';
    }
    void printCell(int row, int column)
    {
        CellState cs = getCellValue(row, column);
        std::string s;
        switch (cs)
        {
        case CellState::EMPTY:
            s = " ";
            break;
        case CellState::X:
            s = "X";
            break;
        case CellState::O:
            s = "O";
            break;

        default:
            break;
        }
        std::cout << s;
    }
    std::bitset<18> getBoardState()
    {
        return boardState;
    }
    void printAscii()
    {
        std::cout << '\n';
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printCell(i, j);
                if (j != 2)
                    std::cout << '|';
            }
            std::cout << '\n';
        }
    }
    void randomizeBoard()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                CellState cs = (CellState)(rand() % 3);
                setCellValue(i, j, cs);
            }
        }
    }
    bool isFull()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (getCellValue(i, j) == CellState::EMPTY)
                    return false;
            }
        }
        return true;
    }

private:
    // Each 2 bits represents a cell
    std::bitset<18> boardState;
};
