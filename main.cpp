#include "Board.hpp"
#include "Evaluator.hpp"
int main()
{
    Board b;
    Evaluator e;
    srand(time(NULL));
    std::cout << "Creating empty board:\n";
    b.printAscii();
    std::cout << "\t X Is winning?: " << e.isEnd(b, Board::X) << '\n';
    std::cout << "\t O Is winning?: " << e.isEnd(b, Board::O) << '\n';

    std::cout << "Randomizing board\n";
    b.randomizeBoard();

    b.printAscii();
    std::cout << "\t X Is winning?: " << e.isEnd(b, Board::X) << '\n';
    std::cout << "\t O Is winning?: " << e.isEnd(b, Board::O) << '\n';

    return 0;
}