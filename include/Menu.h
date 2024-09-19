#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <iostream>

#include "Logger.h"
#include "RiderManagerList.h"
#include "MemberList.h"
#include "Util.h"

class Menu {
public:
    enum{
        INVALID_OPTION = 0,
        SEASONS_MENU,
        MEMBERS_MENU,
        RIDERS_MENU,
        RACES_MENU,
        SETTINGS_MENU,
        EXIT_MAIN_MENU,
    };

private:
    std::shared_ptr<Logger> m_Logger;
    RiderManagerList m_RiderManagerList;
    MemberList m_MemberList;
public:
    Menu();
    explicit Menu(std::shared_ptr<Logger> logger);
    void InitializeMenu(const std::string &selectedSeason);

    void PrintMenu();
    void MainMenu();

    int OptionSelector(const std::string &option);
};



#endif //UNTITLED_MENU_H
