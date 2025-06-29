#pragma once
#include "Board.hpp"
#include <stdint.h>

class Evaluator
{
public:
    // Evaluates if a specific state
    bool isEnd(Board &b, Board::CellState state)
    {
        bool shift = (state == Board::CellState::X); // If it is X we need to shift the values by 1
        std::bitset<18> boardState = b.getBoardState();
        for (std::bitset<18> i : OWinningStates)
        {
            std::bitset<18> comp = shift ? (i << 1) : (i);
            std::bitset<18> temp = (boardState & comp);
            // std::cout << "Comparing state " << i << ": " << temp << '\n';
            if (temp == comp)
                return true;
        }
        return false;
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