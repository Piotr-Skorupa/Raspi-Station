#pragma once
#include <memory>

enum class Status
{
    Avaible = 0,
    Disable = 1,
    Pending = 2
};

class ISensor
{
public:
    virtual ~ISensor(){}

    virtual double getData() = 0;
    virtual void sendData() = 0;

};

typedef ISensorPtr std::unique_ptr<ISensor>;
