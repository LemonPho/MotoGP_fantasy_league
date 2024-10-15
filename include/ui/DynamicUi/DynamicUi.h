#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "core/Logger.h"
#include "utils/Util.h"

class DynamicUi {
private:
    std::shared_ptr<Logger> m_Logger;

    std::vector<std::string> &m_Instructions;
    std::vector<std::string> &m_MenuOptions;

    std::vector<bool> m_Selections;

    size_t m_LeftArrow, m_RightArrow;

    size_t m_HighLightedOption = 0;
    size_t m_InstructionsLength = 0;
    size_t m_OptionCount = 0;
    bool m_Terminate = false;

    //implement mod operator for menu out of bounds

    void gotoxy(size_t x, size_t y);
    //int CheckIfSelected(size_t query);

public:
    DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

    std::vector<bool>& GetSelections();

    void StartUi();
    void Display();
    void Navigate(const char key);
    virtual void OnSelect();
    virtual void OnDeselect();
   
    virtual ~DynamicUi() = default;
};

#ifdef _WIN32
enum keys {
    UP_KEY = 80,
    DOWN_KEY = 72,
    ENTER_KEY = 13,
    BACKSPACE_KEY = 8,
    Q_KEY = 113,
};
#else
enum keys {
    UP_KEY = 66,
    DOWN_KEY = 65,
    ENTER_KEY = 10,
    BACKSPACE_KEY = 127,
    Q_KEY = 113,
};
#endif


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
