#include "XOEngine.hpp"
#include "Tester.hpp"
int main()
{
    Tester t("./draw.xo");
    XOEngine e;
    // e.start();
    t.runTest();
    return 0;
}