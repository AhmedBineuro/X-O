#include "XOEngine.hpp"
#include "./tests/Tester.hpp"
int main()
{
    Tester t("./tests/games/draw.xo");
    XOEngine e;
    // e.start();
    t.runTest();
    return 0;
}