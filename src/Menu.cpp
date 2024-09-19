#include "Menu.h"

Menu::Menu(){
    m_Logger = nullptr;
}

Menu::Menu(std::shared_ptr<Logger> logger){
    m_Logger = logger;
    m_MemberList = MemberList(logger);
    m_RiderManagerList = RiderManagerList(logger);
}

void Menu::InitializeMenu(const std::string &selectedSeason) {
    RiderManagerList riderManagerList(m_Logger);
    MemberList memberList(m_Logger);

    m_Logger->Log("Loading data from files", Logger::LogLevelInfo, Logger::LogFile);

    memberList.ReadFromDisk(util::APP_DIRECTORY_DATA/(selectedSeason + util::MEMBER_DATA));
    riderManagerList.ReadFromDisk(util::APP_DIRECTORY_DATA/(selectedSeason + util::RIDER_DATA));
    m_Logger->Log("Menu initialized", Logger::LogLevelSuccess, Logger::LogFile);
    MainMenu();
}

void Menu::PrintMenu(){
    system(CLEAR);

    std::cout << "Main Menu" << std::endl;
    m_Logger->PrintLog();
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
    m_Logger->Log("Opening Main Menu", Logger::LogLevelInfo, Logger::LogFile);

    bool end = false;
    std::string option;

    do{
        PrintMenu();
        std::cin >> option;
        //menu selection
        switch(OptionSelector(option)){
            case INVALID_OPTION: {
                m_Logger->Log("Invalid Option (" + option + ")", Logger::LogLevelError, Logger::LogConsoleFile);
                break;
            }
            case SEASONS_MENU: {
                break;
            }

            case MEMBERS_MENU: {
                break;
            }

            case RIDERS_MENU: {
                break;
            }

            case RACES_MENU: {
                break;
            }

            case SETTINGS_MENU: {
                break;
            }

            case EXIT_MAIN_MENU: {
                m_Logger->Log("Exiting Main Menu", Logger::LogLevelInfo, Logger::LogFile);
                end = true;
                break;
            }

            default: {
                m_Logger->Log("Invalid Option (" + option + ")", Logger::LogLevelError, Logger::LogConsoleFile);
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
