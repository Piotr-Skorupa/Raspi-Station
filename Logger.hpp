#pragma once

#include <ostream>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

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

    std::ostream& operator<<(const char* text);
    std::ostream& operator<<(LogType text);

private:
    std::string componentName_;
};