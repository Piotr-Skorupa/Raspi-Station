#include "Logger.hpp"
#include <chrono>
#include <iomanip>
#include <ctime>

Logger::Logger(std::string componentName)
    :componentName_("[" + componentName + "]")
    {}

Logger::~Logger()
    {}

Logger& Logger::operator<<(const std::string& text)
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

Logger& Logger::operator<<(const int& text)
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

Logger& Logger::operator<<(const double& text)
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

Logger& Logger::operator<<(const float& text)
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

Logger& Logger::operator<<(const LogType& type)
{
    char tmbuf[32];
    time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	strftime(tmbuf, sizeof(tmbuf), "%F %T", std::localtime(&t));

    file_.open("syslog.log", std::fstream::in | std::fstream::out | std::fstream::app);
    
    if (file_.good())
    {
        switch (type)
        {
        case INFO:
            file_ << tmbuf << " < INFO > " << componentName_ << ": ";
            file_.close();
            return *this;
        case DEBUG:
            file_ << tmbuf << " < DEBUG > " << componentName_ << ": ";
            file_.close();
            return *this;
        case ERROR:
            file_ << tmbuf << " < ERROR > " << componentName_ << ": ";
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
