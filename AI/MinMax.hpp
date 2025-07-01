#include "./Board.hpp"
#include "./XOEngine.hpp"

class MinMaxAi
{
public:
    MinMaxAi() {}
    int evaluate(Board b, int depth = 5, bool max = true)
    {
        Evaluator::EndCondition ec;
        int output;
        if (depth == 0)
        {
            Board::CellState ocs = (this->cs == Board::CellState::X) ? Board::CellState::O : Board::CellState::X;
            ec = ev.isEnd(b);
            if (ec.ended)
            {
                if (ec.winner == cs)
                {
                    output = 1;
                }
                else if (ec.winner == ocs)
                {
                    output = -1;
                }
                else
                {
                    output = 0;
                }
            }
        }
        else if (max)
        {
            std::vector<Board::Play> empty = b.getEmptySlots();
            int val = -1 * INFINITY;
            for (auto play : empty)
            {
                b.setCellValue(play.row, play.column, this->cs);
                int score = evaluate(b, depth - 1, !max);
                b.setCellValue(play.row, play.column, Board::CellState::EMPTY);
                if (score > val)
                    val = score;
            }
            output = val;
        }
        else
        {
            std::vector<Board::Play> empty = b.getEmptySlots();
            int val = INFINITY;
            for (auto play : empty)
            {
                b.setCellValue(play.row, play.column, this->cs);
                int score = evaluate(b, depth - 1, !max);
                b.setCellValue(play.row, play.column, Board::CellState::EMPTY);
                if (score < val)
                    val = score;
            }
            output = val;
        }
        return output;
    }
    void setState(Board::CellState state = Board::CellState::X)
    {
        cs = state;
    }
    Board::Play decidePlay(Board b)
    {
        std::vector<Board::Play> empty = b.getEmptySlots();
        int val = -1 * INFINITY;
        Board::Play p;
        for (auto play : empty)
        {
            b.setCellValue(play.row, play.column, this->cs);
            int score = evaluate(b);
            b.setCellValue(play.row, play.column, Board::CellState::EMPTY);
            if (score > val)
            {
                val = score;
                p = play;
            }
        }
    }

private:
    Evaluator ev;
    Board::CellState cs;
};