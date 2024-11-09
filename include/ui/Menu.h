#pragma once

#include <iostream>

#include "models/Season.h"
#include "core/Logger.h"
#include "views/RiderManagerList.h"
#include "views/MemberList.h"
#include "utils/Util.h"
#include "ui/MemberMenu.h"
#include "ui/SeasonMenu.h"

class Menu {
public:
    enum options{
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
    std::shared_ptr<Season> m_Season;
public:
    Menu();
    void InitializeMenu(std::shared_ptr<Logger> logger, const std::string &selectedSeason);

    void PrintMenu();
    void MainMenu();

    int OptionSelector(const std::string &option);
};
