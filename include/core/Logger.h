#ifndef UNTITLED_LOGGER_H
#define UNTITLED_LOGGER_H

#include <iostream>
#include <fstream>
#include <utility>
#include <ctime>
#include <filesystem>
#include <cstdlib>
#include <string>

class Logger {
public:
    enum LogLevel{
        LogLevelSuccess = 0,
        LogLevelInfo,
        LogLevelWarning,
        LogLevelError,
    };

    enum LogResult{
        LogLevelIncorrect = 0,
        LogLevelInvalid,
        LogFileNotOpen,
        LogSuccessful,
    };

    enum LogTo{
        LogConsoleFile = 0,
        LogConsole = 1,
        LogFile = 2,
    };

private:
    int m_LogLevel;
    std::string m_LogString;
    std::ofstream m_LogFile;
public:
    Logger();
    explicit Logger(int logLevel);
    ~Logger();

    void InitializeFile(const std::filesystem::path& appDirectory);

    void Log(const std::string &message, LogLevel logLevel, LogTo logDestination);
    LogResult LogToConsole(const std::string &message, LogLevel logLevel);
    LogResult LogToFile(const std::string &message, LogLevel logLevel);

    void PrintLog();
    void ResetLogString();
};




#endif //UNTITLED_LOGGER_H
