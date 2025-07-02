#include "./AI/MinMax.hpp"
#include "./XOEngine.hpp"
int main()
{
    // MinMaxAi m;
    // m.setState(Board::CellState::X);
    // Board b;
    // b.setCellValue(0, 0, Board::CellState::O);
    // b.setCellValue(1, 0, Board::CellState::X);
    // b.setCellValue(2, 2, Board::CellState::O);
    // b.setCellValue(2, 0, Board::CellState::X);
    // b.setCellValue(2, 1, Board::CellState::O);
    // std::cout << "Before AI play" << "Optimal choice is 1,1\n";
    // b.printAscii();
    // Board::Play p = m.decidePlay(b);
    // b.setCellValue(p.row, p.column, Board::CellState::X);
    // std::cout << "After AI play" << "AI choice is " << p.row << "," << p.column << '\n';
    // b.printAscii();
    srand(time(NULL));
    XOEngine xoe;
    xoe.start();
    return 0;
}