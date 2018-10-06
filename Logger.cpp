#include "Logger.hpp"
#include <chrono>
#include <iomanip>

Logger::Logger(std::string componentName)
    :componentName_("[" + componentName + "]")
    {}

Logger::~Logger()
    {}

Logger& Logger::operator<<(const char* text)
{
    file_.open("syslog.log", std::fstream::in | std::fstream::out | std::fstream::app);
    if (file_.good())
    {
        file_ << text;
        file_.close();
    }else
    {
        std::cerr << "[SYSTEM]: Can't write to syslog" << std::endl;
    }
    
    return *this;
}

Logger& Logger::operator<<(LogType type)
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    
    file_.open("syslog.log", std::fstream::in | std::fstream::out | std::fstream::app);
    if (file_.good())
    {
        switch (type)
        {
        case INFO:
            file_ << std::put_time(std::localtime(&now_c), "%c")
                << " < INFO > " << componentName_ << ": ";
            file_.close();
            return *this;
            // return std::cout << std::put_time(std::localtime(&now_c), "%c")
            //     << " < INFO > " << componentName_ << ": ";
        case DEBUG:
            file_ << std::put_time(std::localtime(&now_c), "%c")
                << " < DEBUG > " << componentName_ << ": ";
            file_.close();
            return *this;
            // return std::cout << std::put_time(std::localtime(&now_c), "%c")
            //     << " < DEBUG > " << componentName_ << ": ";
        case ERROR:
            file_ << std::put_time(std::localtime(&now_c), "%c")
                << " < ERROR > " << componentName_ << ": ";
            file_.close();
            return *this;   
            // return std::cout << std::put_time(std::localtime(&now_c), "%c")
            //     << " < ERROR > " << componentName_ << ": ";
        }
    }
    else
        std::cerr << "[SYSTEM]: Can't create log file" << std::endl;
        return *this;
}
