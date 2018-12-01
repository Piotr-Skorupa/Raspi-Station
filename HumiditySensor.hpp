#pragma once

#include "ISensor.hpp"
#include "Logger.hpp"

#include <boost/optional.hpp>
//testing from this
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

// this class is now testing Humidity Sensor


class HumiditySensor
    : public ISensor
{
public:
    HumiditySensor();
    ~HumiditySensor();
    
    double getTemperature();
    double getHumidity();
    Status getStatus() const;

    int getData() override;
    void writeData(int data) override;

private:
    Logger logger_;
    Status status_;
    boost::optional<double> humidityData_;
    boost::optional<double> temperatureData_;
};
