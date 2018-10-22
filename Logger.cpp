#include "Logger.hpp"
#include <chrono>
#include <iomanip>

Logger::Logger(std::string componentName)
    :componentName_("[" + componentName + "]")
    {}

Logger::~Logger()
    {}

Logger& Logger::operator<<(std::string text)
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

Logger& Logger::operator<<(int text)
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

Logger& Logger::operator<<(double text)
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

Logger& Logger::operator<<(float text)
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
        case DEBUG:
            file_ << std::put_time(std::localtime(&now_c), "%c")
                << " < DEBUG > " << componentName_ << ": ";
            file_.close();
            return *this;
        case ERROR:
            file_ << std::put_time(std::localtime(&now_c), "%c")
                << " < ERROR > " << componentName_ << ": ";
            file_.close();
            return *this;   
        }
    }
    else
    {
        std::cerr << "[SYSTEM]: Can't write to syslog" << std::endl;
    }
        
    return *this;
}

void Logger::clearLogFile()
{
    std::ofstream file;
    file.open("syslog.log");
    if (file.good())
    {
        file.close();
    }
    else
    {
        std::cerr << "[SYSTEM]: Can't write to syslog" << std::endl;
    }
}
