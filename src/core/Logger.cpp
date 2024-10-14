//
// Created by mishu on 11/09/2024.
//

#include "Logger.h"

Logger::Logger() {
    m_LogLevel = LogLevelSuccess;
    m_LogString = "";
}

Logger::Logger(int logLevel) {
    m_LogLevel = logLevel;
    m_LogString = "";
}

Logger::~Logger(){
    Log("Closing log file", LogLevelInfo, LogFile);
    m_LogFile.close();
}

void Logger::InitializeFile(const std::filesystem::path& appDirectory) {
    //create file name, with date and time
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[25];
    std::filesystem::path fileName;

    strftime(timestamp, sizeof(timestamp), "Log_%Y-%m-%d_%H-%M-%S", timeinfo);
    fileName = appDirectory / "Logs" / (std::string(timestamp) + ".txt");
    m_LogFile.open(fileName, std::ios::out);

    //check if the file wasn't able to be created
    if(!m_LogFile.is_open()){
        LogToConsole("Could not create log file", LogLevelError);
    }

    //file created
    Log("Log file created", LogLevelInfo, LogFile);
}

void Logger::Log(const std::string &message, LogLevel logLevel, LogTo logDestination){
    switch(logDestination){
        case LogConsoleFile: {
            int consoleResult = LogToConsole(message, logLevel);
            int fileResult = LogToFile(message, logLevel);
            std::string tempString;

            if(fileResult == LogFileNotOpen){
                LogToConsole("Log file not open", LogLevelWarning);
            }

            if(fileResult == LogLevelIncorrect){
                tempString = "Incorrect log level set for message: " + message + " with log level: " + std::to_string(logLevel);
                LogToFile(tempString, LogLevelError);
            } else if(consoleResult == LogLevelIncorrect){
                tempString = "Incorrect log level set for console message: " + message + " with log level: " + std::to_string(logLevel);
                LogToFile(tempString, LogLevelError);
            }
            break;
        }

        case LogConsole: {
            int consoleResult = LogToConsole(message, logLevel);
            std::string tempString;

            if(consoleResult == LogLevelInvalid){
                LogToFile(message, logLevel);
            } else if(consoleResult == LogLevelIncorrect){
                tempString = "Incorrect log level set for console message: " + message + " with log level: " + std::to_string(logLevel);
                LogToFile(tempString, LogLevelWarning);
            }

            break;
        }

        case LogFile: {
            int fileResult = LogToFile(message, logLevel);
            std::string tempString;

            if(fileResult == LogFileNotOpen){
                LogToConsole("It was not possible to create the log file", LogLevelWarning);
            } else if(fileResult == LogLevelIncorrect){
                tempString = "Incorrect log level set for message: " + message + " with log level: " + std::to_string(logLevel);
                LogToFile(tempString, LogLevelError);
            }

            break;
        }

        default: {
            std::string tempString = "Message: " + message + " was logged with an incorrect log level setting (" + std::to_string(logLevel) + ")";
            int fileResult = LogToFile(tempString, LogLevelError);

            if(fileResult == LogFileNotOpen){
                LogToConsole("It was not possible to create the log file", LogLevelWarning);
            }
        }
    }
}

//only to be used by the log function, to log to console use Log(message, logLevel, logger::LogConsole)
Logger::LogResult Logger::LogToConsole(const std::string &message, LogLevel logLevel) {
    //check the log level that is wanted to be created is the log level saved in the instance
    if(logLevel < m_LogLevel){
        return LogLevelInvalid;
    }

    //save to log string and file based on log level
    std::string tempString;
    switch(logLevel){
        case LogLevelSuccess: {
            m_LogString += "\033[32m[SUCCESS]: \033[0m" + message + "\n";
            break;
        }

        case LogLevelInfo: {
            m_LogString += "\033[36m[INFO]: \033[0m" + message + "\n";
            break;
        }

        case LogLevelWarning: {
            m_LogString += "\033[33m[WARNING]: \033[0m" + message + "\n";
            break;
        }

        case LogLevelError: {
            m_LogString += "\033[31m[ERROR]: \033[0m" + message + "\n";
            break;
        }

        default: {
            return LogLevelIncorrect;
        }
    }

    return LogSuccessful;
}

//only to be used by the log function, to log to file use Log(message, logLevel, logger::LogFile)
Logger::LogResult Logger::LogToFile(const std::string &message, LogLevel logLevel) {
    //if log level is below the one defined in the model then dont log
    if(logLevel < m_LogLevel){
        return LogLevelInvalid;
    }

    //make sure log file is open
    if(!m_LogFile.is_open()){
        return LogFileNotOpen;
    }

    //create timestamp of log
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", timeinfo);

    //save based on log level
    switch(logLevel){
        case LogLevelSuccess: {
            m_LogFile << timestamp << " [SUCCESS]: " << message << std::endl;
            break;
        }

        case LogLevelInfo: {
            m_LogFile << timestamp << " [INFO]: " << message << std::endl;
            break;
        }

        case LogLevelWarning: {
            m_LogFile << timestamp << " [WARNING]: " << message << std::endl;
            break;
        }

        case LogLevelError: {
            m_LogFile << timestamp << " [ERROR]: " << message << std::endl;
            break;
        }

        default: {
            m_LogFile << timestamp << "[ERROR]: Incorrect log level defined for message: " << message << std::endl;
            return LogLevelIncorrect;
        }
    }

    return LogSuccessful;
}

//for printing log to the console, logs are deleted after printing, it serves as error messages
void Logger::PrintLog(){
    if(m_LogString.empty()){
        return;
    }
    std::cout << m_LogString;
    ResetLogString();
}

void Logger::ResetLogString() {
    m_LogString = "";
}
