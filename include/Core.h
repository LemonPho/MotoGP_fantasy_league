#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H

#include <iostream>

#include "Menu.h"
#include "Logger.h"
#include "RiderManagerList.h"
#include "MemberList.h"
#include "Util.h"

class Core {
private:
    std::shared_ptr<Logger> m_Logger = std::make_shared<Logger>();
    Menu m_Menu;
    std::string m_SelectedSeason;
public:
    Core();

    void InitializeCore();
    void FirstStart();
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
