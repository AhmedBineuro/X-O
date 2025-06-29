#include "Tester.hpp"

int main()
{
    Tester t;
    std::string path = "./tests/games/";
    std::string rowFileBase = "row";
    std::string colFileBase = "col";
    std::string extension = ".xo";
    std::cout << "\n________Starting test suite________\n";
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
    std::cout << "\n________Test suite finished________\n";
}