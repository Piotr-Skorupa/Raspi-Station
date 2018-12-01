#pragma once

#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include <ctime>
#include <iostream>
#include <string>
#include <random>
#include "src/mqtt/async_client.h"
#include "Logger.hpp"

using namespace std;
using namespace std::chrono;

class MqttConnector
{
public:
    MqttConnector();
    ~MqttConnector();
    int publish(std::string topic, std::string message);

private:
    Logger logger_;
    const std::string DFLT_ADDRESS;
    const int QOS;
    const int MAX_BUFFERED_MSGS;  // 120 * 5sec => 10min off-line buffering
    const std::string PERSIST_DIR;
    mqtt::async_client cli;
};