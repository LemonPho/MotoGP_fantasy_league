#include "core/Core.h"

Core::Core() {
#ifdef _WIN32
    const char* appDataPath = getenv("APPDATA");
    std::filesystem::path tempDirectory = appDataPath;

    if(!std::filesystem::exists(tempDirectory)){
        std::cout << "The appdata roaming path was not found, press enter to close" << std::endl;
        std::cin.ignore();
        exit(0);
    }

    util::APP_DIRECTORY = tempDirectory / "MotoGP Fantasy League";
    util::APP_DIRECTORY_LOG = util::APP_DIRECTORY / "logs";
    util::APP_DIRECTORY_DATA = util::APP_DIRECTORY / "data";

    if(!std::filesystem::exists(util::APP_DIRECTORY)){
        std::filesystem::create_directory(util::APP_DIRECTORY);
    }

    if(!std::filesystem::exists(util::APP_DIRECTORY_LOG)){
        std::filesystem::create_directory(util::APP_DIRECTORY_LOG);
    }

    if(!std::filesystem::exists(util::APP_DIRECTORY_DATA)){
        std::filesystem::create_directory(util::APP_DIRECTORY_DATA);
    }

    PWSTR downloadsPath = nullptr;

    //locate downloads folder
    if(SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &downloadsPath))){
        util::DOWNLOADS_DIRECTORY = std::filesystem::path(downloadsPath);
    } else {
        m_Logger->Log("Could not locate downloads directory", Logger::LogLevelWarning, Logger::LogConsoleFile);
    }

    //free memory
    if(downloadsPath){
        CoTaskMemFree(downloadsPath);
    }

    m_Menu = Menu(m_Logger);
#else

#endif
}

void Core::InitializeCore() {
    m_Logger->InitializeFile(util::APP_DIRECTORY);
    m_Logger->Log("Finding program data file", Logger::LogLevelInfo, Logger::LogFile);

    if(!std::filesystem::exists(util::APP_DIRECTORY_DATA)){
        m_Logger->Log("Data directory was not found, program was not able to create it", Logger::LogLevelError, Logger::LogConsoleFile);
        m_Logger->PrintLog();
        std::cout << "Press enter to exit" << std::endl;
        std::cin.ignore();
        exit(0);
    }

    std::filesystem::path programData = util::APP_DIRECTORY_DATA / util::PROGRAM_DATA;

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

            //open the file after having created the season
            programFile.open(util::APP_DIRECTORY_DATA/util::PROGRAM_DATA);
            if(!programFile.is_open()){
                m_Logger->Log("Couldn't open the program data file", Logger::LogLevelError, Logger::LogConsoleFile);
            } else {
                std::getline(programFile, tempString, '\n');
                m_SelectedSeason = tempString;
            }
        } else {
            m_SelectedSeason = tempString;
            m_Logger->Log("Checking data files with season: " + tempString, Logger::LogLevelInfo, Logger::LogFile);
            std::ifstream membersFile(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::MEMBER_DATA));
            std::ifstream ridersFile(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::RIDER_DATA));
            std::ifstream racesFile(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::RACE_DATA));

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

    m_Menu.InitializeMenu(m_SelectedSeason);
}

void Core::FirstStart() {
    m_Logger->Log("Creating program data files", Logger::LogLevelInfo, Logger::LogFile);
    std::ofstream programData(util::APP_DIRECTORY_DATA/util::PROGRAM_DATA, std::ios::out);

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

        std::ofstream file1(util::APP_DIRECTORY_DATA/(input + util::MEMBER_DATA));
        std::ofstream file2(util::APP_DIRECTORY_DATA/(input + util::RACE_DATA));
        std::ofstream file3(util::APP_DIRECTORY_DATA/(input + util::RIDER_DATA));

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