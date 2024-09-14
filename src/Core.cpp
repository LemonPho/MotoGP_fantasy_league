#include "Core.h"

Core::Core() {
    const char* appDataPath = getenv("APPDATA");
    std::filesystem::path tempDirectory = appDataPath;
    std::filesystem::path tempLogDirectory;

    if(!std::filesystem::exists(tempDirectory)){
        std::cout << "The appdata roaming path was not found, closing app" << std::endl;
        std::cin.ignore();
        exit(0);
    }

    m_AppDirectory = tempDirectory / "MotoGP Fantasy League";
    tempLogDirectory = m_AppDirectory / "Logs";

    if(!std::filesystem::exists(m_AppDirectory)){
        std::filesystem::create_directory(m_AppDirectory);
    }

    if(!std::filesystem::exists(tempLogDirectory)){
        std::filesystem::create_directory(tempLogDirectory);
    }

    m_Menu = Menu(m_Logger);
}

//TODO: code what is needed for first start and all that
void Core::InitializeCore() {
    m_Logger->InitializeFile(m_AppDirectory);
    m_Logger->Log("Core initialized", logger::LogLevelInfo, logger::LogFile);
    m_Menu.InitializeMenu();
}

void Core::FirstStart() {

}