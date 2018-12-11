#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>
#include <string>
#include <sstream>
#include <csignal>

#include "Logger.hpp"
#include "MqttConnector.hpp"
#include "PressureSensor.hpp"
#include "HumiditySensor.hpp"
#include "Camera.hpp"


static int exitCode = 0;
static Logger logger("MainComponent");

std::string doubleToString(double decimalNumber)
{
        std::ostringstream strs;
        strs << decimalNumber;
        return strs.str();
}

void signalHandler(int signalNumber)
{
    logger << INFO << "System correctly shutdown." << ENDL;
    exitCode = signalNumber;
    exit(exitCode);
}

int main(int argc, char* argv[])
{
    high_resolution_clock::time_point startTimer = high_resolution_clock::now();
    Logger::clearLogFile();
    std::cout << "Program is starting..." << std::endl;
    
    std::shared_ptr<MqttConnector> connector = std::make_shared<MqttConnector>();
    std::unique_ptr<Camera> camera(new Camera());
    std::unique_ptr<PressureSensor> pressureSensor(new PressureSensor());
    std::unique_ptr<HumiditySensor> humiditySensor(new HumiditySensor());

    camera->makePhoto();

    std::cout << "Start!" << std::endl;

    std::string tempString, pressString, humString;
    int gettingResult = 0;

    std::signal(SIGTERM, signalHandler);
    std::signal(SIGINT, signalHandler);

    while (true)
    {
        if (!Camera::isRecording)
        {
            gettingResult = pressureSensor->getData();

            if (gettingResult < 0)
            {
                logger << ERROR << "Something go wrong. Trying to get temp from second sensor..." << ENDL;
                pressString = "can't get data";
                tempString = "can't get data";

                gettingResult = humiditySensor->getData();

                if (gettingResult < 0 && pressureSensor->getStatus() == Status::Disable 
                    && humiditySensor->getStatus() == Status::Disable)
                {
                    exitCode = 1;
                    logger << ERROR << "Sensors are not working. Please check connections."
                        << " Program will shutdown!" << ENDL;
                    exit(exitCode);
                }
                else if (gettingResult < 0)
                {
                    goto jumpToLoopNextStep;
                }
                else
                {
                    tempString = doubleToString(humiditySensor->getTemperature());
                    humString = doubleToString(humiditySensor->getHumidity());
                }
            }
            else
            {
                pressString = doubleToString(pressureSensor->getPressure());
                tempString = doubleToString(pressureSensor->getTemperature());

                gettingResult = humiditySensor->getData();
                if (gettingResult < 0)
                {
                    goto jumpToLoopNextStep;
                }
                else{
                    humString = doubleToString(humiditySensor->getHumidity());
                }
            }
            jumpToLoopNextStep:

            connector->publish("SENSORS/PRESSURE", pressString);
            connector->publish("SENSORS/TEMPERATURE", tempString);
            connector->publish("SENSORS/HUMIDITY", humString);
        }
        else{
            std::string picture = camera->recording();
            if (!picture.empty())
                connector->publish("SENSORS/CAMERA_PIC", picture);
        }
        
        high_resolution_clock::time_point endTimer = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(endTimer - startTimer);
        std::cout << "Duration: " << time_span.count() << " seconds." << std::endl;

        if (time_span.count() / 3600 >= 3)
        {
            // clearing syslog file after 3 hours
            Logger::clearLogFile();
            logger << INFO << "Previous logs have been cleared because the saving time has been exceeded." << ENDL;
            startTimer = high_resolution_clock::now();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "The end" << std::endl;
    return exitCode;
}
