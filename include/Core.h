#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H

#include "Menu.h"

class Core {
private:
    Menu menu;
public:
    Core();

    void InitializeCore();
    void FirstStart();
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_CORE_H
