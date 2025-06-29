#include "XOEngine.hpp"
#include "Tester.hpp"
int main()
{
    Tester t("./test.txt");
    XOEngine e;
    e.start();
    // t.printTest();
    // t.runTest();
    return 0;
}