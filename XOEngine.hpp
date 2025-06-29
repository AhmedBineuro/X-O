#pragma once
#include "Evaluator.hpp"

class XOEngine
{
public:
    XOEngine(Board::CellState first = Board::CellState::EMPTY)
    {
        switch (first)
        {
        case Board::CellState::EMPTY:
        {
            srand(time(NULL));
            xTurn = (bool)(rand() % 2);
            break;
        }
        default:
        {
            xTurn = (Board::CellState::X == first);
            break;
        }
        }
        ended = false;
    }
    void printAsciiBoard()
    {
        this->b.printAscii();
    }
    // Return -1 for nothing, 0 for tie, 1 for X win and 2 for y win
    int start()
    {
        std::cout << "Starting X-O game!\n";
        while (!ended)
        {
            b.printAscii();
            std::string player = (xTurn) ? "X" : "O";
            Board::CellState cellState = (xTurn) ? Board::CellState::X : Board::CellState::O;
            std::cout << player << "\'s turn\n";
            int row = -1, column = -1;
            std::cout << "Type the row location of play: ";
            std::cin >> row;
            std::cout << "Type the column location of play: ";
            std::cin >> column;
            while (!playTurn(row - 1, column - 1) && !b.isFull())
            {
                std::cout << "Type the row location of play: ";
                std::cin >> row;
                std::cout << "Type the column location of play: ";
                std::cin >> column;
            }
            if (e.isEnd(b, cellState))
            {
                std::cout << player << " won!!!\n";
                return cellState;
            }
            if (b.isFull())
                ended = true;
        }
        return 0;
    }
    int step(int row, int column, bool printAscii = true)
    {
        std::string player = (xTurn) ? "X" : "O";
        Board::CellState cellState = (xTurn) ? Board::CellState::X : Board::CellState::O;
        if (printAscii)
            this->b.printAscii();
        std::cout << player << "\'s turn\n";
        playTurn(row - 1, column - 1);
        if (e.isEnd(b, cellState))
        {
            std::cout << player << " won!!!\n";
            return cellState;
        }
        if (b.isFull())
            return 0;
        return -1;
    }

    // Return true if play was successful
    bool playTurn(int row, int column)
    {
        if (row >= 3 || column >= 3 || row < 0 || column < 0)
        {
            std::cout << "Index out of bounds\n";
            return false;
        }
        if (b.getCellValue(row, column) != Board::CellState::EMPTY)
        {
            std::cout << "Cell occupied\n";
            return false;
        }
        Board::CellState cs = (xTurn) ? Board::CellState::X : Board::CellState::O;
        b.setCellValue(row, column, cs);
        xTurn = !xTurn;
        return true;
    }
    void reset(Board::CellState first = Board::CellState::EMPTY)
    {
        b.reset();
        switch (first)
        {
        case Board::CellState::EMPTY:
        {
            xTurn = (bool)(rand() % 2);
            break;
        }
        default:
        {
            xTurn = (Board::CellState::X == first);
            break;
        }
        }
    }

private:
    Board b;
    Evaluator e;
    bool xTurn, ended;
};