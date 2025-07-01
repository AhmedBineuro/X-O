#include "./Board.hpp"
#include "./XOEngine.hpp"

class MinMaxAi
{
public:
    struct MinMaxOutput
    {
        int score = 0;
        Board::Play play;
    };
    MinMaxAi() {}
    MinMaxOutput evaluate(Board b, int depth = 4, bool max = true)
    {
        Evaluator::EndCondition ec;
        std::vector<Board::Play> empty = b.getEmptySlots();
        MinMaxOutput output;
        if (depth == 0)
        {
            // output.score = ev.isEnd(b, cs).ended;
            // for (int i = 0; i < 8; i++)
            // {
            //     int score = ev.getCount(b.;
            // }
        }
        // Maximize case
        else if (max)
        {
            int i = -1 * INFINITY;
            for (auto e : empty)
            {
                b.setCellValue(e.row, e.column, cs);
                MinMaxOutput evaluatedScore = evaluate(b, depth - 1, !max);
                // i = (i > evaluatedScore.score) ? ;
                b.setCellValue(e.row, e.column, Board::CellState::EMPTY);
            }
        }
        // Minimize case
        else
        {
            int i = INFINITY;
            int i = -1 * INFINITY;
            for (auto e : empty)
            {
                b.setCellValue(e.row, e.column, cs);
                // score += evaluate(b, depth - 1, !max);
                b.setCellValue(e.row, e.column, Board::CellState::EMPTY);
            }
        }
        return output;
    }
    void setState(Board::CellState state = Board::CellState::X)
    {
        cs = state;
    }

private:
    Evaluator ev;
    Board::CellState cs;
};