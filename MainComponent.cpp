#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>
#include <string>
#include "Logger.hpp"
#include "MqttConnector.hpp"

int main(int argc, char* argv[])
{
    Logger::clearLogFile();
    std::cout << "Start" << std::endl;
    Logger logger("MainComponent");
   
    logger << INFO << "Raspi Weather Station !" << ENDL;
    logger << DEBUG << "Tu Piotrek" << ENDL;
    logger << ERROR << "test error" << ENDL;
    logger << INFO << "Siema " << 5 << ", " << 5.14 << ", " << 6.3f << ENDL;
	std::cout << "MQTT test ... to exit CTRL+C" << std::endl;
	MqttConnector server;
	server.publish("DEVICES", "czy te urzadzenia dzialaja ?");

    return 0;
}