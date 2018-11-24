#pragma once

#include "ISensor.hpp"
#include "MqttConnector.hpp"
#include "Logger.hpp"

#include <boost/optional.hpp>
//testing from this
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

// this class is now testing Pressure Sensor
// testing I2C

class PressureSensor 
    final: public ISensor
{
public: 
    PressureSensor();
    ~PressureSensor();

    void getData() override;
    int sendData() override;
    void writeData(int data) override;

private:
    MqttConnector connector_;
    Logger logger_;
    Status status_;
    boost::optional<double> pressureData_;
    boost::optional<double> temperatureData_;
};