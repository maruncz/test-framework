#include "testmanager.h"

int main()
{
    return (testManager::getInstance().runAllTests()) ? 0 : 1;
}
