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
    }
    void printAsciiBoard()
    {
        this->b.printAscii();
    }
    // Will start 2 player game
    Evaluator::EndCondition start()
    {
        std::cout << "Starting X-O game!\n";
        while (true)
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
            Evaluator::EndCondition ec = e.isEnd(b);
            if (ec.ended)
            {
                std::cout << player << " won!!!\n";
                std::cout << "Winning pattern: " << e.stringifyPattern(ec.wp) << '\n';
                return ec;
            }
            if (b.isFull())
            {
                std::cout << "Draw!\n";
                return {Evaluator::WinPattern::Draw, Board::CellState::EMPTY, true};
            }
        }
        return {Evaluator::WinPattern::None, Board::CellState::EMPTY, true};
    }
    // Will perform one play and 1 check for winning patterns
    Evaluator::EndCondition step(int row, int column, bool printAscii = true)
    {
        std::string player = (xTurn) ? "X" : "O";
        Board::CellState cellState = (xTurn) ? Board::CellState::X : Board::CellState::O;
        if (printAscii)
            this->b.printAscii();
        std::cout << player << "\'s turn\n";
        playTurn(row - 1, column - 1);
        Evaluator::EndCondition ec = e.isEnd(b);
        if (ec.ended)
        {
            std::cout << player << " won!!!\n";
            std::cout << "Winning pattern: " << e.stringifyPattern(ec.wp) << '\n';
            return ec;
        }
        if (b.isFull())
        {
            std::cout << "Draw!\n";
            return {Evaluator::WinPattern::Draw, Board::CellState::EMPTY, true};
        }
        return {Evaluator::WinPattern::None, Board::CellState::EMPTY, false};
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
    Board getBoard()
    {
        return b;
    }

private:
    Board b;
    Evaluator e;
    bool xTurn;
};