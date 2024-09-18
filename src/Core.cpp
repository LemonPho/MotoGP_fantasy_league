#include "Core.h"

Core::Core() {
    const char* appDataPath = getenv("APPDATA");
    std::filesystem::path tempDirectory = appDataPath;
    std::filesystem::path tempLogDirectory;

    if(!std::filesystem::exists(tempDirectory)){
        std::cout << "The appdata roaming path was not found, press enter to close" << std::endl;
        std::cin.ignore();
        exit(0);
    }

    m_AppDirectory = tempDirectory / "MotoGP Fantasy League";
    tempLogDirectory = m_AppDirectory / "logs";
    m_AppDirectoryData = m_AppDirectory / "data";

    if(!std::filesystem::exists(m_AppDirectory)){
        std::filesystem::create_directory(m_AppDirectory);
    }

    if(!std::filesystem::exists(tempLogDirectory)){
        std::filesystem::create_directory(tempLogDirectory);
    }

    if(!std::filesystem::exists(m_AppDirectoryData)){
        std::filesystem::create_directory(m_AppDirectoryData);
    }

    m_Menu = Menu(m_Logger);
}

//TODO: code what is needed for first start and all that
void Core::InitializeCore() {
    m_Logger->InitializeFile(m_AppDirectory);
    m_Logger->Log("Finding program data file", Logger::LogLevelInfo, Logger::LogFile);

    if(!std::filesystem::exists(m_AppDirectoryData)){
        m_Logger->Log("Data directory was not found, program was not able to create it", Logger::LogLevelError, Logger::LogConsoleFile);
        m_Logger->PrintLog();
        std::cout << "Press enter to exit" << std::endl;
        std::cin.ignore();
        exit(0);
    }

    std::filesystem::path programData = m_AppDirectoryData / PROGRAM_DATA;

    if(!std::filesystem::exists(programData)){
        m_Logger->Log("Program data file not found, creating", Logger::LogLevelInfo, Logger::LogFile);
        FirstStart();
    } else {
        std::ifstream programFile(programData);
        std::string tempString;

        if(!programFile.is_open()){
            m_Logger->Log("Could not open program file", Logger::LogLevelError, Logger::LogConsoleFile);
            m_Logger->PrintLog();
            std::cout << "Press enter to exit" << std::endl;
            std::cin.ignore();
            exit(0);
        }

        std::getline(programFile, tempString, '\n');

        if(tempString.empty() || tempString == " "){
            m_Logger->Log("Program data file empty, starting first start", Logger::LogLevelInfo, Logger::LogFile);
            FirstStart();
        } else {
            *m_SelectedSeason = tempString;
            m_Logger->Log("Checking data files with season: " + tempString, Logger::LogLevelInfo, Logger::LogFile);
            std::ifstream membersFile(m_AppDirectoryData/(tempString + MEMBER_DATA));
            std::ifstream ridersFile(m_AppDirectoryData/(tempString + RIDER_DATA));
            std::ifstream racesFile(m_AppDirectoryData/(tempString + RACE_DATA));

            if(!membersFile.is_open() || !ridersFile.is_open() || !racesFile.is_open()){
                m_Logger->Log("Could not open one of the program files", Logger::LogLevelError, Logger::LogConsoleFile);
                m_Logger->PrintLog();
                std::cout << "Press enter to exit" << std::endl;
                std::cin.ignore();
                exit(0);
            }

            m_Logger->Log("Files successfully found", Logger::LogLevelSuccess, Logger::LogFile);
        }
    }

    m_Logger->Log("Core initialized", Logger::LogLevelSuccess, Logger::LogFile);

    m_Menu.InitializeMenu();
}

void Core::FirstStart() {
    m_Logger->Log("Creating program data files", Logger::LogLevelInfo, Logger::LogFile);
    std::ofstream programData(m_AppDirectoryData/PROGRAM_DATA, std::ios::out);

    if(!programData.is_open()){
        m_Logger->Log("Could not create the program data file", Logger::LogLevelError, Logger::LogConsoleFile);
        m_Logger->PrintLog();
        std::cout << "Press enter to exit" << std::endl;
        std::cin.ignore();
        exit(0);
    }

    bool end = false;

    while(!end){
        std::string input;

        std::cout << "First Start" << std::endl;
        std::cout << "Input the season year: ";
        std::cin >> input;

        m_Logger->Log("Creating program files with season name: " + input, Logger::LogLevelInfo, Logger::LogFile);

        std::ofstream file1(m_AppDirectoryData/(input + MEMBER_DATA));
        std::ofstream file2(m_AppDirectoryData/(input + RACE_DATA));
        std::ofstream file3(m_AppDirectoryData/(input + RIDER_DATA));

        if(!file1.is_open() || !file2.is_open() || !file3.is_open()){
            m_Logger->Log("Could not create files with the season name: " + input, Logger::LogLevelError, Logger::LogFile);
            system(CLEAR);
            std::cout << "Be sure to not include invalid characters in the name (spaces, /, *, etc)" << std::endl;
        } else {
            programData << input << std::endl;
            programData.close();
            file1.close();
            file2.close();
            file3.close();
            end = true;
        }
    }

    m_Logger->Log("Files successfully created", Logger::LogLevelSuccess, Logger::LogFile);


}