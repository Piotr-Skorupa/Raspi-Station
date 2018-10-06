#include <iostream>
#include "Logger.hpp"

int main()
{
    Logger logger("MainComponent");
    logger << INFO << "Raspi Weather Station !" << std::endl;
    return 0;
}