#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_DYNAMICUI_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "core/Logger.h"
#include "utils/Util.h"

struct Window {
    int columns=0;
    int rows=0;
};

class DynamicUi {
private:
    std::shared_ptr<Logger> m_Logger;

    std::vector<std::string> &m_Instructions;
    std::vector<std::string> &m_MenuOptions;
    std::vector<bool> m_Selections;
    
    size_t m_InstructionsLength = 0;
    size_t m_LongestMenuOption = 0;
    size_t m_OptionCount = 0;

    size_t m_HighlightedOption = 0;
    size_t m_OptionIndex = 0;
    bool m_Terminate = false;

protected:
    Window m_Window;
    void gotoxy(size_t x, size_t y);
    void GetWindowDimensions(int& columns, int& rows);
    void ToggleConsoleCursor(bool enable);
    void UpdateArrowPosition(size_t line, size_t left, size_t right);
    void ClearText(size_t start, size_t end, size_t left, size_t right);
public:
    DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

    std::vector<bool>& GetSelections();
    size_t GetHighlightedOption();
    size_t GetOptionCount();
    size_t GetInstructionsLength();

    void InitializeUi();
    void Display();
    void Navigate(const char key);
    virtual void OnSelect();
    virtual void OnDeselect();
    virtual void Exit();
   
    virtual ~DynamicUi() = default;
};

enum UiSpacing {
    INSTRUCTIONS_DOWN = 2,
    ARROWS = 3,
    SELECT = 7,
    ACCEPT = 1,
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
