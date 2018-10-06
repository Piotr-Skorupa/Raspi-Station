#include "Logger.hpp"

Logger::Logger(std::string componentName)
    :componentName_("[" + componentName + "]")
    {}

Logger::~Logger()
    {}

std::ostream& Logger::operator<<(const char* text)
{
    return std::cout << text;
}

std::ostream& Logger::operator<<(LogType type)
{
    switch (type)
    {
    case INFO:
        return std::cout << " < INFO > " << componentName_ << ": ";
    case DEBUG:
        return std::cout << " < DEBUG > " << componentName_ << ": ";
    case ERROR:
        return std::cout << " < ERROR > " << componentName_ << ": ";
    }
}
