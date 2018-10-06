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

#define INFO LogType::Info
#define DEBUG LogType::Debug
#define ERROR LogType::Error

class Logger
{
public:
    Logger() = delete;
    Logger(std::string componentName);
    Logger(const Logger& other) = delete;
    Logger(const Logger&& other) = delete;
    ~Logger();

    Logger& operator<<(const char* text);
    Logger& operator<<(LogType text);

private:
    std::string componentName_;
    std::fstream file_;
};