#ifndef UNTITLED_LOGGER_H
#define UNTITLED_LOGGER_H

#include <iostream>
#include <fstream>
#include <utility>
#include <ctime>
#include <filesystem>
#include <cstdlib>

namespace logger{
    enum {
        LogLevelInfo = 0,
        LogLevelWarning,
        LogLevelError,
    };

    enum {
        LogLevelIncorrect = 0,
        LogFileNotOpen = 1,
        LogSuccessful = 2,
    };
    class Logger {

    private:
        int m_LogLevel;
        std::string m_LogString;
        std::ofstream m_LogFile;
    public:
        Logger();
        explicit Logger(int logLevel);
        ~Logger();

        void InitializeFile(const std::filesystem::path& appDirectory);

        //log to console automatically logs to file
        void LogToConsole(const std::string &message, const int logLevel);
        int LogToFile(const std::string &message, const int logLevel);

        void PrintLog();
        void ResetLogString();
    };
}



#endif //UNTITLED_LOGGER_H
