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
#define DATA_READING_SIZE 60

// example usage : logger << INFO << "Some text" << ENDL;

class Logger
{
public:
    Logger() = delete;
    Logger(std::string componentName);
    Logger(const Logger& other) = delete;
    Logger(const Logger&& other) = delete;
    ~Logger();

    Logger& operator<<(std::string text);
    Logger& operator<<(const char* text);
    Logger& operator<<(int text);
    Logger& operator<<(double text);
    Logger& operator<<(float text);
    Logger& operator<<(LogType text);

    static void clearLogFile();

private:
    std::string componentName_;
    std::fstream file_;
};