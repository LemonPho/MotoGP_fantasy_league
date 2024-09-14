#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H

#include <iostream>

#include "Menu.h"
#include "Logger.h"

class Core {
private:
    std::shared_ptr<logger::Logger> m_Logger = std::make_shared<logger::Logger>();
    Menu m_Menu;
    std::filesystem::path m_AppDirectory;
public:
    Core();

    void InitializeCore();
    void FirstStart();
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
