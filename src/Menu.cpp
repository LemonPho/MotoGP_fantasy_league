#include "Menu.h"

Menu::Menu(){
    const char* appDataPath = getenv("APPDATA");
    std::filesystem::path tempDirectory = appDataPath;
    std::filesystem::path tempLogDirectory = appDataPath;

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
}

//basically initialize the whole program
void Menu::InitializeMenu() {
    m_Logger.InitializeFile(m_AppDirectory);

    MainMenu();
}

void Menu::PrintMenu(){
    system(CLEAR);

    std::cout << "Main Menu" << std::endl;
    m_Logger.PrintLog();
    std::cout << "1. Seasons Menu" << std::endl;
    std::cout << "2. Members Menu" << std::endl;
    std::cout << "3. Riders Menu" << std::endl;
    std::cout << "4. Races Menu" << std::endl;
    std::cout << "5. Settings" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Option" << std::endl;
    std::cout << "-> ";
}

void Menu::MainMenu() {
    bool end = false;
    std::string option;

    do{
        PrintMenu();
        std::cin >> option;
        //menu selection
        switch(OptionSelector(option)){
            case INVALID_OPTION: {
                m_Logger.LogToFile("Invalid Option", logger::LogLevelInfo);
                break;
            }
            case SEASONS_MENU: {
                m_Logger.LogToFile("Opening Seasons Menu", logger::LogLevelInfo);
                break;
            }

            case MEMBERS_MENU: {
                m_Logger.LogToFile("Opening Members Menu", logger::LogLevelInfo);
                break;
            }

            case RIDERS_MENU: {
                m_Logger.LogToFile("Opening Riders Menu", logger::LogLevelInfo);
                break;
            }

            case RACES_MENU: {
                m_Logger.LogToFile("Opening Races Menu", logger::LogLevelInfo);
                break;
            }

            case SETTINGS_MENU: {
                m_Logger.LogToFile("Opening Settings Menu", logger::LogLevelInfo);
                break;
            }

            case EXIT_MAIN_MENU: {
                m_Logger.LogToFile("Exiting Main Menu", logger::LogLevelInfo);
                end = true;
                break;
            }

            default: {
                m_Logger.LogToFile("Invalid Option", logger::LogLevelInfo);
                break;
            }
        }
    }while(!end);
}

//for converting string to int in the menu options, this is done so that the program doesn't crash if a number
//isn't inputted
int Menu::OptionSelector(const std::string &option) {
    if(option == "1") return SEASONS_MENU;
    if(option == "2") return MEMBERS_MENU;
    if(option == "3") return RIDERS_MENU;
    if(option == "4") return RACES_MENU;
    if(option == "5") return SETTINGS_MENU;
    if(option == "6") return EXIT_MAIN_MENU;
    return 0;
}
