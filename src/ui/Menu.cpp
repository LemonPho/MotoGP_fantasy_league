#include "ui/Menu.h"

Menu::Menu(){
    m_Logger = std::make_shared<Logger>();
    m_Season = std::make_shared<Season>();
}

void Menu::InitializeMenu(std::shared_ptr<Logger> logger, const std::string &selectedSeason, bool finalized) {
    m_Logger = logger;
    m_Logger->Log("Initializing main menu", Logger::LogLevelInfo, Logger::LogFile);
    RiderManagerList riderManagerList(m_Logger);
    MemberList memberList(m_Logger);

    m_Season->InitializeSeason(logger, selectedSeason, finalized);
    m_Logger->Log("Main menu initialized", Logger::LogLevelSuccess, Logger::LogFile);
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
                SeasonMenu seasonMenu;
                seasonMenu.InitializeSeasonMenu(m_Logger, m_Season);
                break;
            }

            case MEMBERS_MENU: {
                MemberMenu memberMenu;
                memberMenu.InitializeMemberMenu(m_Logger, m_Season);
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
