#pragma once
#include <memory>

//testing from this
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

enum class Status
{
    Enable = 0,
    Disable = 1,
    Pending = 2
};

enum class Connecting
{
    Success = 0,
    Error = -1
};

class ISensor
{
public:
    virtual ~ISensor(){}

    virtual int getData() = 0;
};

typedef std::unique_ptr<ISensor> ISensorPtr;
