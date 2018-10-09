#include <iostream>
#include <chrono>
#include <thread>
#include "Logger.hpp"

int main()
{
    Logger::clearLogFile();
    std::cout << "Start" << std::endl;
    Logger logger("MainComponent");
    logger << INFO << "Raspi Weather Station !" << ENDL;
    logger << DEBUG << "Tu Piotrek" << ENDL;
    logger << ERROR << "test error" << ENDL;
    logger << INFO << "Siema " << 5 << ", " << 5.14 << ", " << 6.3f << ENDL;

    std::cout << "waiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    logger << INFO << "koniec czekania :)" << ENDL;
    std::cout << "end" << std::endl;

    return 0;
}