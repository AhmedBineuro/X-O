#pragma once
#include "Board.hpp"
#include <stdint.h>

class Evaluator
{
public:
    enum WinPattern
    {
        None,
        Row0,
        Row1,
        Row2,
        Col0,
        Col1,
        Col2,
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
        case Row0:
            return "Row 1";
        case Row1:
            return "Row 2";
        case Row2:
            return "Row 3";
        case Col0:
            return "Column 1";
        case Col1:
            return "Column 2";
        case Col2:
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
    // Evaluates if a specific state
    EndCondition isEnd(Board &b, Board::CellState state)
    {
        bool shift = (state == Board::CellState::X); // If it is X we need to shift the values by 1
        std::bitset<18> boardState = b.getBoardState();
        int index = 1;
        for (std::bitset<18> i : OWinningStates)
        {
            std::bitset<18> comp = shift ? (i << 1) : (i);
            std::bitset<18> temp = (boardState & comp);
            // std::cout << "Comparing state " << i << ": " << temp << '\n';
            if (temp == comp)
                return {(WinPattern)index, state, true};
            index++;
        }
        return {(WinPattern)index, state, false};
    }

private:
    template <size_t N>
    std::bitset<N> reverseBitset(const std::bitset<N> &b)
    {
        std::bitset<N> reversed;
        for (size_t i = 0; i < N; ++i)
        {
            reversed[i] = b[N - 1 - i];
        }
        return reversed;
    }
    std::bitset<18> OWinningStates[8] = {
        21,    // Row 0 Horizontal
        1344,  // Row 1 Horizontal
        86016, // Row 2 Horizontal
        4161,  // Column 0 Vertical
        16644, // Column 1 Vertical
        66576, // Column 2 Vertical
        65793, // Left to Right Diagonal
        4368   // Right to Left Diagonal
    };
};