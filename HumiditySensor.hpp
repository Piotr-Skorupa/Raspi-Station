#pragma once

#include "ISensor.hpp"
#include "Logger.hpp"
#include <boost/optional.hpp>

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

private:
    Logger logger_;
    Status status_;
    boost::optional<double> humidityData_;
    boost::optional<double> temperatureData_;
};
