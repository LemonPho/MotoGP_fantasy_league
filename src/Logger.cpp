//
// Created by mishu on 11/09/2024.
//

#include "Logger.h"

using namespace logger;

Logger::Logger() {
    m_LogLevel = LogLevelInfo;
    m_LogString = "";
}

Logger::Logger(int logLevel) {
    m_LogLevel = logLevel;
    m_LogString = "";
}

Logger::~Logger(){
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
    LogToFile("Log file created", LogLevelInfo);
}

void Logger::LogToConsole(const std::string &message, const int logLevel) {
    //check the log level that is wanted to be created is the log level saved in the instance
    if(logLevel < m_LogLevel){
        return;
    }

    //save to log string and file based on log level
    std::string tempString;
    switch(logLevel){
        case LogLevelInfo: {
            m_LogString += "[INFO]: " + message + "\n";
            LogToFile(message, LogLevelInfo);
            break;
        }

        case LogLevelWarning: {
            m_LogString += "[WARNING]" + message + "\n";
            LogToFile(message, LogLevelWarning);
            break;
        }

        case LogLevelError: {
            m_LogString += "[ERROR]: " + message + "\n";
            LogToFile(message, LogLevelError);
            break;
        }

        default: {
            tempString = "Incorrect log level set for message: " + message;
            LogToFile(tempString, LogLevelWarning);
            break;
        }
    }
}

int Logger::LogToFile(const std::string &message, const int logLevel) {
    //if log level is below the one defined in the model then dont log
    if(logLevel < m_LogLevel){
        return LogLevelIncorrect;
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
        case LogLevelInfo: {
            m_LogFile << timestamp << " [INFO]: " << message << std::endl;
            break;
        }

        case LogLevelWarning: {
            m_LogFile << timestamp << "[WARNING]: " << message << std::endl;
            break;
        }

        case LogLevelError: {
            m_LogFile << timestamp << "[ERROR]: " << message << std::endl;
            break;
        }

        default: {
            m_LogFile << timestamp << "[ERROR]: Incorrect log level defined for message: " << message << std::endl;
            break;
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
