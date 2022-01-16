#include "testmanager.h"

int main(int argc, char *argv[])
{
    testManager::getInstance().runAllBenchmarks();
    return 0;
}

