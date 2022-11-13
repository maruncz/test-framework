#include "testmanager.h"

int main()
{
    testManager::getInstance().runAllBenchmarks();
    return 0;
}
