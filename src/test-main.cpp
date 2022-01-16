#include "testmanager.h"

int main(int argc, char *argv[])
{
    testManager::getInstance().runAllTests();
    return 0;
}
