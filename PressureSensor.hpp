#pragma once

#include "ISensor.hpp"
#include "Logger.hpp"
#include <boost/optional.hpp>

class PressureSensor 
    final: public ISensor
{
public: 
    PressureSensor();
    ~PressureSensor();

    double getTemperature();
    double getPressure();
    Status getStatus() const;

    int getData() override;

private:
    Logger logger_;
    Status status_;
    boost::optional<double> pressureData_;
    boost::optional<double> temperatureData_;
};