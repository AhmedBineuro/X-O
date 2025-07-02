#pragma once
#include "Board.hpp"
#include <stdint.h>

class Evaluator
{
public:
    enum WinPattern
    {
        None,
        Row1,
        Row2,
        Row3,
        Col1,
        Col2,
        Col3,
        LRDiag,
        RLDiag,
        Draw
    };
    static std::string stringifyPattern(WinPattern wp)
    {
        switch (wp)
        {
        case None:
            return "None";
        case Row1:
            return "Row 1";
        case Row2:
            return "Row 2";
        case Row3:
            return "Row 3";
        case Col1:
            return "Column 1";
        case Col2:
            return "Column 2";
        case Col3:
            return "Column 3";
        case LRDiag:
            return "Left to Right Diagonal";
        case RLDiag:
            return "Right to Left Diagonal";
        case Draw:
            return "Draw";
        default:
            return "";
        }
    };
    struct EndCondition
    {
        WinPattern wp;
        Board::CellState winner;
        bool ended;
    };
    // Counts how many of a state is in a win pattern
    int getCount(Board b, Board::CellState cs = Board::CellState::EMPTY, WinPattern wp = WinPattern::Row1)
    {
        int count;
        if (wp == Evaluator::WinPattern::None)
            return 0;
        Board bClone = b;
        std::bitset<18> wpMask;
        wpMask = (cs == Board::CellState::X) ? (OWinningStates[wp - 1] << 1) : (OWinningStates[wp - 1]);
        std::bitset<18> bitset;
        if (cs == Board::CellState::EMPTY)
        {
            bitset = (b.getBoardState() & OWinningStateMasks[wp - 1]);
            count = 3 - bitset.count();
        }
        else
        {
            bitset = (b.getBoardState() & OWinningStateMasks[wp - 1]) & wpMask;
            count = bitset.count();
        }
        return count;
    }
    // Evaluates if a specific state
    EndCondition isEnd(Board &b)
    {
        std::bitset<18> boardState = b.getBoardState();
        int index = 1;
        // Checking if O won
        for (std::bitset<18> i : OWinningStates)
        {
            std::bitset<18> temp = (boardState & i);
            if (temp == i)
                return {(WinPattern)index, Board::CellState::O, false};
            index++;
        }
        // Checking if X won
        for (std::bitset<18> i : OWinningStates)
        {
            std::bitset<18> comp = (i << 1);
            std::bitset<18> temp = (boardState & comp);
            if (temp == comp)
                return {(WinPattern)index, Board::CellState::X, true};
            index++;
        }
        if (b.isFull())
            return {WinPattern::Draw, Board::CellState::EMPTY, true};
        return {(WinPattern)index, Board::CellState::EMPTY, false};
    }

private:
    std::bitset<18> OWinningStates[8] = {
        86016, // Row 0 Horizontal
        1344,  // Row 1 Horizontal
        21,    // Row 2 Horizontal
        66576, // Column 0 Vertical
        16644, // Column 1 Vertical
        4161,  // Column 2 Vertical
        65793, // Left to Right Diagonal
        4368   // Right to Left Diagonal
    };
    std::bitset<18> OWinningStateMasks[8] = {
        258048, // Row 0 Horizontal
        4032,   // Row 1 Horizontal
        63,     // Row 2 Horizontal
        199728, // Column 0 Vertical
        49932,  // Column 1 Vertical
        12483,  // Column 2 Vertical
        197379, // Left to Right Diagonal
        13104   // Right to Left Diagonal
    };
};