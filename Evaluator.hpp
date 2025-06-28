#pragma once
#include "Board.hpp"
#include <stdint.h>

class Evaluator
{
public:
    // Evaluates if a specific state
    bool isEnd(Board &b, Board::CellState state)
    {
        bool shift = (state == Board::CellState::O); // If it is O we need to shift the values by 1
        std::bitset<18> boardStateAsInt = static_cast<uint32_t>(b.getBoardState().to_ulong());
        for (std::bitset<18> i : XWinningStates)
        {
            std::bitset<18> comp = shift ? (i) : (i >> 1);
            std::bitset<18> temp = (boardStateAsInt & comp);
            // std::cout << "Comparing state " << i << ": " << temp << '\n';
            if (temp == comp)
                return true;
        }
        return false;
    }

private:
    // To get the O winning states bit shit to the left by 1
    std::bitset<18> XWinningStates[8] = {
        86016, // Row 0 Horizontal
        1344,  // Row 1 Horizontal
        21,    // Row 2 Horizontal
        66576, // Column 0 Vertical
        16644, // Column 1 Vertical
        4161,  // Column 2 Vertical
        65793, // Left to Right Diagonal
        4368   // Right to Left Diagonal
    };
};