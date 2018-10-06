#include <iostream>
#include <chrono>
#include <thread>
#include "Logger.hpp"

int main()
{
    std::cout << "Start" << std::endl;
    Logger logger("MainComponent");
    logger << INFO << "Raspi Weather Station !" << "\n";
    logger << DEBUG << "Tu Piotrek" << "\n";
    logger << ERROR << "Ja nie rozumiem czemu to nie dziala xd" << "\n";

    std::cout << "waiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    logger << INFO << "koniec czekania :)" << "\n";
    std::cout << "end" << std::endl;

    return 0;
}