#include "XOEngine.hpp"
#include "./tests/Tester.hpp"
int main()
{
    Evaluator ev;
    Board b;
    b.setCellValue(0, 0, Board::CellState::X);
    b.setCellValue(1, 1, Board::CellState::O);
    b.setCellValue(2, 2, Board::CellState::X);
    std::cout << "Bit count: " << ev.getCount(b, Board::CellState::O, Evaluator::WinPattern::LRDiag) << '\n';
    std::cout << "Real bits: " << b.getBoardState() << '\n';
    std::cout << "Empty slots:\n";
    std::vector<Board::Play> empty = b.getEmptySlots();
    b.printAscii();
    for (auto p : empty)
        std::cout << "Row: " << p.row << " Col: " << p.column << '\n';
    // t.runTest();
    return 0;
}