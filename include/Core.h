#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H

#include <iostream>

#include "Menu.h"
#include "Logger.h"

const std::string PROGRAM_DATA = "program-data.txt";
const std::string MEMBER_DATA = "-member-data.txt";
const std::string RIDER_DATA = "-rider-data.txt";
const std::string RACE_DATA = "-race-data.txt";

class Core {
private:
    std::shared_ptr<Logger> m_Logger = std::make_shared<Logger>();
    Menu m_Menu;
    std::filesystem::path m_AppDirectory;
    std::filesystem::path m_AppDirectoryData;
    std::shared_ptr<std::string> m_SelectedSeason = std::make_shared<std::string>();
public:
    Core();

    void InitializeCore();
    void FirstStart();
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
