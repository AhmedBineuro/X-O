#pragma once
#include "Tester.hpp"
void patternValidityCheck()
{
    Tester t;
    std::string path = "./tests/games/";
    std::string rowFileBase = "row";
    std::string colFileBase = "col";
    std::string extension = ".xo";
    std::cout << "\n________Starting Pattern test suite________\n";
    // Row checks for both X and O
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            std::string testName = rowFileBase + std::to_string(i) + ((j == 0) ? "X" : "O") + extension;
            std::string fullUrl = path + testName;
            std::cout << "Starting test: " << testName + "\n";
            t.loadTest(fullUrl);
            Evaluator::EndCondition ec = t.runTest();
            assert(t.sameOutcome(ec) && ("Failed test " + testName).c_str());
        }
    }

    // Column checks for both X and O
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            std::string testName = colFileBase + std::to_string(i) + ((j == 0) ? "X" : "O") + extension;
            std::string fullUrl = path + testName;
            std::cout << "Starting test: " << testName + "\n";
            t.loadTest(fullUrl);
            Evaluator::EndCondition ec = t.runTest();
            assert(t.sameOutcome(ec) && ("Failed test " + testName).c_str());
        }
    }

    // Left Right Diagonal checks for both X and O
    for (int j = 0; j < 2; j++)
    {
        std::string testName = "lrdiag";
        testName += ((j == 0) ? "X" : "O") + extension;
        std::string fullUrl = path + testName;
        std::cout << "Starting test: " << testName + "\n";
        t.loadTest(fullUrl);
        Evaluator::EndCondition ec = t.runTest();
        assert(t.sameOutcome(ec) && ("Failed test " + testName).c_str());
    }

    // Right Left Diagonal checks for both X and O
    for (int j = 0; j < 2; j++)
    {
        std::string testName = "rldiag";
        testName += ((j == 0) ? "X" : "O") + extension;
        std::string fullUrl = path + testName;
        std::cout << "Starting test: " << testName + "\n";
        t.loadTest(fullUrl);
        Evaluator::EndCondition ec = t.runTest();
        assert(t.sameOutcome(ec) && ("Failed test " + testName).c_str());
    }

    // Simplified version removed in favour of ordered testing
    //  for (const auto &it : std::filesystem::directory_iterator(path))
    //  {
    //      t.loadTest(it.path());
    //      Evaluator::EndCondition ec = t.runTest();
    //      assert(t.sameOutcome(ec));
    //  }
    std::cout << "\n________Test suite finished________\n";
}
void countTests()
{
    std::cout << "\n________Starting Counting test suite________\n";
    Evaluator ev;
    Board b;
    int count = 0;

    // Row 1 populated checks
    b.setCellValue(0, 0, Board::CellState::X);
    b.setCellValue(0, 1, Board::CellState::O);
    b.setCellValue(0, 2, Board::CellState::X);
    count = ev.getCount(b, Board::CellState::EMPTY, Evaluator::WinPattern::Row1);
    std::cout << "Empty count in "
              << Evaluator::stringifyPattern(Evaluator::WinPattern::Row1)
              << " pattern: " << count << '\n';
    b.printAscii();
    assert(count == 0);
    b.reset();

    // Row 2 populated checks
    b.setCellValue(1, 0, Board::CellState::X);
    b.setCellValue(1, 1, Board::CellState::X);
    b.setCellValue(1, 2, Board::CellState::X);
    count = ev.getCount(b, Board::CellState::X, Evaluator::WinPattern::Row2);
    std::cout << "X count in "
              << Evaluator::stringifyPattern(Evaluator::WinPattern::Row2)
              << " pattern: " << count << '\n';
    b.printAscii();
    assert(count == 3);
    b.reset();

    // Row 3 populated checks
    b.setCellValue(0, 0, Board::CellState::X);
    b.setCellValue(0, 1, Board::CellState::O);
    b.setCellValue(0, 2, Board::CellState::X);
    count = ev.getCount(b, Board::CellState::O, Evaluator::WinPattern::Row3);
    std::cout << "O count in "
              << Evaluator::stringifyPattern(Evaluator::WinPattern::Row3)
              << " pattern: " << count << '\n';
    b.printAscii();
    assert(count == 0);
    b.reset();

    // Column 1 populated checks
    b.setCellValue(0, 0, Board::CellState::X);
    b.setCellValue(1, 0, Board::CellState::O);
    b.setCellValue(2, 0, Board::CellState::X);
    count = ev.getCount(b, Board::CellState::EMPTY, Evaluator::WinPattern::Col1);
    std::cout << "Empty count in "
              << Evaluator::stringifyPattern(Evaluator::WinPattern::Col1)
              << " pattern: " << count << '\n';
    b.printAscii();
    assert(count == 0);
    b.reset();

    // Column 2 populated checks
    b.setCellValue(0, 1, Board::CellState::X);
    b.setCellValue(1, 1, Board::CellState::X);
    b.setCellValue(2, 1, Board::CellState::X);
    count = ev.getCount(b, Board::CellState::X, Evaluator::WinPattern::Col2);
    std::cout << "X count in "
              << Evaluator::stringifyPattern(Evaluator::WinPattern::Col2)
              << " pattern: " << count << '\n';
    b.printAscii();
    assert(count == 3);
    b.reset();

    // Column 3 populated checks
    b.setCellValue(0, 2, Board::CellState::X);
    b.setCellValue(1, 2, Board::CellState::O);
    b.setCellValue(2, 2, Board::CellState::X);
    count = ev.getCount(b, Board::CellState::O, Evaluator::WinPattern::Col3);
    std::cout << "O count in "
              << Evaluator::stringifyPattern(Evaluator::WinPattern::Col3)
              << " pattern: " << count << '\n';
    b.printAscii();
    assert(count == 1);
    b.reset();

    // LR Diagonal populated check
    b.setCellValue(0, 0, Board::CellState::X);
    b.setCellValue(1, 1, Board::CellState::O);
    b.setCellValue(2, 2, Board::CellState::X);
    count = ev.getCount(b, Board::CellState::X, Evaluator::WinPattern::LRDiag);
    std::cout << "X count in "
              << Evaluator::stringifyPattern(Evaluator::WinPattern::LRDiag)
              << " pattern: " << count << '\n';
    b.printAscii();
    assert(count == 2);
    b.reset();

    // LR Diagonal populated check
    b.setCellValue(0, 2, Board::CellState::X);
    b.setCellValue(1, 1, Board::CellState::O);
    b.setCellValue(2, 0, Board::CellState::X);
    count = ev.getCount(b, Board::CellState::O, Evaluator::WinPattern::RLDiag);
    std::cout << "O count in "
              << Evaluator::stringifyPattern(Evaluator::WinPattern::RLDiag)
              << " pattern: " << count << '\n';
    b.printAscii();
    assert(count == 1);
    b.reset();

    std::cout
        << "\n________Test suite finished________\n";
}