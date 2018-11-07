#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>
#include <string>
#include "Logger.hpp"
#include "MqttConnector.hpp"
#include "PressureSensor.hpp"

int main(int argc, char* argv[])
{
    Logger::clearLogFile();
    std::cout << "Start" << std::endl;
    Logger logger("MainComponent");

    std::cout << "Logger test ..." << std::endl;
    logger << INFO << "Raspi Weather Station !" << ENDL;
    logger << DEBUG << "Start" << ENDL;
    logger << ERROR << "Test error" << ENDL;
    logger << INFO << "Test value types: " << 5 << ", " << 5.14 << ", " << 6.3f << ENDL;

    std::cout << "I2C test..." << std::endl;
    ISensorPtr dioda(new PressureSensor());
    auto tempData = dioda->getData();

    std::cout << "MQTT test ... to exit CTRL+C" << std::endl;
    MqttConnector server;
    server.publish("DEVICES", "czy te urzadzenia dzialaja ?");

    return 0;
}