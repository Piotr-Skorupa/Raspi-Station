#pragma once

#include <ostream>
#include <fstream>
#include <iostream>
#include <string>


enum class LogType
{
    Info,
    Debug,
    Error
};

#define INFO LogType::Info           //use the type, if you want to add date and time to your log
#define DEBUG LogType::Debug          
#define ERROR LogType::Error
#define ENDL "\n"                    //use it instead of "std::endl"

// example usage : logger << INFO << "Some text" << ENDL;

class Logger
{
public:
    Logger() = delete;
    Logger(std::string componentName);
    Logger(const Logger& other) = delete;
    Logger(const Logger&& other) = delete;
    ~Logger();

    Logger& operator<<(const std::string& text);
    Logger& operator<<(const char* text);
    Logger& operator<<(const int& text);
    Logger& operator<<(const double& text);
    Logger& operator<<(const float& text);
    Logger& operator<<(const LogType& text);

    static void clearLogFile();

private:
    std::string componentName_;
    std::fstream file_;
};