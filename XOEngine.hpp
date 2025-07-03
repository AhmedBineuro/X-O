#pragma once
#include "Evaluator.hpp"
#include "./AI/MinMax.hpp"

class XOEngine
{
public:
    XOEngine(Board::CellState first = Board::CellState::EMPTY, Board::CellState player = Board::CellState::X)
    {
        switch (first)
        {
        case Board::CellState::EMPTY:
        {
            srand(time(0));
            xTurn = (bool)(rand() % 2);
            break;
        }
        default:
        {
            xTurn = (Board::CellState::X == first);
            break;
        }
        }
        this->player = player;
        m.setState((this->player == Board::CellState::X) ? Board::CellState::O : Board::CellState::X);
    }
    void printAsciiBoard()
    {
        this->b.printAscii();
    }
    void setPlayer(Board::CellState cs)
    {
        this->player = cs;
        m.setState((this->player == Board::CellState::X) ? Board::CellState::O : Board::CellState::X);
    }
    // Will start 2 player game
    Evaluator::EndCondition start()
    {
        this->running=true;
        this->b.reset();
        std::cout << "Starting X-O game!\n";
        std::cout << "AI? (y/n): ";
        bool ai = false;
        std::string input;
        std::cin >> input;
        Evaluator::EndCondition output;
        while ((input != "y") && (input != "n"))
        {
            std::cout << "Invalid input, put y for yes or n for no\n";
            std::cin >> input;
        }
        if (input == "y")
            ai = true;
        if(ai){
            input="";
            std::cout << "AI Difficulty? (0-5 [default is 2]): ";
            std::cin >> input;
            while((input.length()>1)||(input.c_str()[0]<'0')||(input.c_str()[0]>'5')){
                std::cout << "Invalid input, put a value between 0 to 5\n";
                std::cin>>input;
            }
            int difficulty=2;
            difficulty=std::stoi(input);
            this->m.setDepthLimit(difficulty);
        }
        while (this->running)
        {
            b.printAscii();
            std::string player = (xTurn) ? "X" : "O";
            Board::CellState cellState = (xTurn) ? Board::CellState::X : Board::CellState::O;
            std::cout << player << "\'s turn\n";
            int row = -1, column = -1;
            if (ai && (this->player != cellState))
            {
                Board::Play p = this->m.decidePlay(this->b);
                row = p.row;
                column = p.column;
                playTurn(row, column);
            }
            else
            {
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
            }
            Evaluator::EndCondition ec = e.isEnd(b);
            if (ec.ended && (ec.wp!=Evaluator::WinPattern::Draw))
            {
                std::cout << player << " won!!!\n";
                std::cout << "Winning pattern: " << e.stringifyPattern(ec.wp) << '\n';
                output= ec;
                this->running=false;
            }
            if (b.isFull())
            {
                std::cout << "Draw!\n";
                output= {Evaluator::WinPattern::Draw, Board::CellState::EMPTY, true};
                this->running=false;
            }
        }
        return output;
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
        Evaluator::EndCondition output = {Evaluator::WinPattern::None, Board::CellState::EMPTY, false};;
        Evaluator::EndCondition ec = e.isEnd(b);
        if (ec.ended && (ec.wp!=Evaluator::WinPattern::Draw))
        {
            std::cout << player << " won!!!\n";
            std::cout << "Winning pattern: " << e.stringifyPattern(ec.wp) << '\n';
            output= ec;
        }
        if (b.isFull())
        {
            std::cout << "Draw!\n";
            output= {Evaluator::WinPattern::Draw, Board::CellState::EMPTY, true};
        }
        return output;
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
    void setDepthLimit(int newDepth){
        this->m.setDepthLimit(newDepth);
    }

private:
    Board b;
    Evaluator e;
    bool xTurn,running=false;;
    Board::CellState player;
    MinMaxAi m;
};