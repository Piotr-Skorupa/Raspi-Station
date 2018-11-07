#pragma once

#include "ISensor.hpp"
#include "MqttConnector.hpp"
#include "Logger.hpp"

//testing from this
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

// this class is now testing for LED diode
// testing I2C

class PressureSensor 
    final: public ISensor
{
public: 
    PressureSensor();
    ~PressureSensor();

    double getData() override;
    void sendData() override;

private:
    MqttConnector connector_;
    Logger logger_;
};