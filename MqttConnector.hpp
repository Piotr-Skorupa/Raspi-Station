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
    //paho
    const std::string DFLT_ADDRESS { "213.222.211.83" };
    const int QOS = 1;
    const int MAX_BUFFERED_MSGS = 120;	// 120 * 5sec => 10min off-line buffering
    const string PERSIST_DIR { "data-persist" };
    //paho end
};