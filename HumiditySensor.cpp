#include "HumiditySensor.hpp"

HumiditySensor::HumiditySensor()
    : logger_("HumiditySensor")
    , status_(Status::Disable)
    {}

HumiditySensor::~HumiditySensor()
    {}

int HumiditySensor::getData()
{
    logger_ << INFO << "Getting data from sensor..." << ENDL;
    status_ = Status::Pending;
    // Create I2C bus
    int file;
    const char *bus = "/dev/i2c-1";
    if((file = open(bus, O_RDWR)) < 0) 
    {
        logger_ << ERROR << "Failed to open the bus." << ENDL;
        return int(Connecting::Error);
    }
    // Get I2C device, SI7021 I2C address is 0x40(64)
    ioctl(file, I2C_SLAVE, 0x40);

    // Send humidity measurement command(0xF5)
    char config[1] = {0xF5};
    write(file, config, 1);
    sleep(1);

    // Read 2 bytes of humidity data
    // humidity msb, humidity lsb
    char data[2] = {0};
    if(read(file, data, 2) != 2)
    {
        logger_ << ERROR << "Input/output Error (can't read humidity from sensor)" 
            << ENDL;
        status_ = Status::Disable;
        return int(Connecting::Error);
    }
    else
    {
        // Convert the data
        humidityData_ = (((data[0] * 256 + data[1]) * 125.0) / 65536.0) - 6;
        logger_ << DEBUG << "Humidity: " << humidityData_.get() << " %" << ENDL;
    }

    // Send temperature measurement command(0xF3)
    config[0] = 0xF3;
    write(file, config, 1); 
    sleep(1);

    status_ = Status::Avaible;
    // Read 2 bytes of temperature data
    // temp msb, temp lsb
    if(read(file, data, 2) != 2)
    {
        logger_ << ERROR << "Input/output Error (can't read temperature from sensor)"
            << ENDL;
        status_ = Status::Disable;
        return int(Connecting::Error);
    }
    else
    {
        // Convert the data to Celsjus
        temperatureData_ = (((data[0] * 256 + data[1]) * 175.72) / 65536.0) - 46.85;
        logger_ << DEBUG << "Temperature(2): " << temperatureData_.get() << " C" << ENDL;
    }

    std::cout << "reading from humidity sensor" << std::endl;
    return (int)Connecting::Success;
}


double HumiditySensor::getHumidity()
{
    if (humidityData_){
        return humidityData_.get();
    }else
    {
        logger_ << INFO << "humidity is empty" << ENDL;
        return 0.0;
    }
}

double HumiditySensor::getTemperature()
{
    if (temperatureData_){
        return temperatureData_.get();
    }else
    {
        logger_ << INFO << "temperature is empty" << ENDL;
        return 0.0;
    }
}

Status HumiditySensor::getStatus() const
{
    return status_;
}
