#include "PressureSensor.hpp"


PressureSensor::PressureSensor()
    :connector_()
    , logger_("PressureSensor")
    {}

PressureSensor::~PressureSensor()
    {}

double PressureSensor::getData()
{
    logger_ << INFO << "Getting data" << ENDL;
    
    int file;
    const char* filename = "/dev/i2c-1";
    if ((file = open(filename, O_RDWR)) < 0) {
        /* ERROR HANDLING: you can check errno to see what went wrong */
        logger_ << ERROR <<"Failed to open the i2c bus" << ENDL;
        exit(1);
    }
    logger_ << INFO << "i2c bus has opened correctly. " << ENDL;

    // TODO
    return 1.0;
}

void PressureSensor::sendData()
{
    logger_ << INFO << "Sending data" << ENDL;
    // TODO
}