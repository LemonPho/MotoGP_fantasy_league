#include "ui/DynamicUi/DynamicUi.h"

DynamicUi::DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions)
    : m_Logger(std::move(logger)), m_Instructions(instructions), m_MenuOptions(menuOptions)
{
    m_Logger->Log("Opening dynamic ui", Logger::LogLevelInfo, Logger::LogFile);
    m_InstructionsLength = m_Instructions.size();
    m_OptionCount = m_MenuOptions.size();
    m_HighlightedOption = m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN_SPACING;
    m_SelectionsSpace.upperLimit = m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN_SPACING;
    m_SelectionsSpace.lowerLimit = m_OptionCount + m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN_SPACING;
}

void DynamicUi::gotoxy(size_t x, size_t y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void DynamicUi::GetWindowDimensions(int& columns, int& rows) {
    m_Logger->Log("Getting console window dimensions", Logger::LogLevelInfo, Logger::LogFile);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        // The number of columns (width)
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        // The number of rows (height)
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else {
        // If the function fails, return some default value
        columns = 80;
        rows = 25;
    }
}

void DynamicUi::ToggleConsoleCursor(bool enable) {
    m_Logger->Log("Disabling console cursor", Logger::LogLevelInfo, Logger::LogFile);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = enable; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


void DynamicUi::UpdateArrowPosition(size_t line, size_t left, size_t right) {
    gotoxy(left, line);
    std::cout << "->";
    gotoxy(right, line);
    std::cout << "<-";
}

void DynamicUi::ClearText(size_t start, size_t end, size_t left, size_t right) {
    for (size_t i = start; i <= end; i++) {
        gotoxy(left, i);
        std::cout << "  ";
        gotoxy(right, i);
        std::cout << "  ";
    }
}

void DynamicUi::ClearLine(size_t line) {
    std::string string(" ", m_Window.columns);
    gotoxy(0, line);
    std::cout << string;
}

std::vector<std::string>& DynamicUi::GetMenuOptions() {
    return m_MenuOptions;
}

size_t DynamicUi::GetLongestMenuOption() {
    return m_LongestMenuOption;
}

size_t DynamicUi::GetHighlightedOption() {
    return m_HighlightedOption;
}

size_t DynamicUi::GetOptionCount() {
    return m_OptionCount;
}

size_t DynamicUi::GetInstructionsLength() {
    return m_InstructionsLength;
}

size_t DynamicUi::GetOptionIndex() {
    return m_OptionIndex;
}

size_t DynamicUi::GetLeftArrow() {
    return m_LeftArrow;
}

size_t DynamicUi::GetRightArrow() {
    return m_RightArrow;
}

bool DynamicUi::GetChangesMade() {
    return m_ChangesMade;
}

SelectionsSpace DynamicUi::GetSelectionsSpace() {
    return m_SelectionsSpace;
}

void DynamicUi::InitializeUi() {
    m_Logger->Log("Starting dynamic ui", Logger::LogLevelInfo, Logger::LogFile);
    m_Terminate = false;
    ToggleConsoleCursor(false);
    util::GetWindowDimensions(m_Window.columns, m_Window.rows);

    //finding longest option to place arrows
    for (auto& menuOption : m_MenuOptions) {
        if (menuOption.length() > m_LongestMenuOption) {
            m_LongestMenuOption = menuOption.length();
        }
    }

    //generating initial arrow positioning
    m_LeftArrow = (m_Window.columns / 2 - m_LongestMenuOption / 2) - UiSpacing::ARROWS_SPACING;
    m_RightArrow = (m_Window.columns / 2 + m_LongestMenuOption / 2) + UiSpacing::ARROWS_SPACING;
    char key;

    //display instructions and menu
    Display();
    while (!m_Terminate) {
        PrintLog();
        //updating menu
        UpdateArrowPosition(m_HighlightedOption, m_LeftArrow, m_RightArrow);

        key = util::CustomGetch();
        ClearText(m_HighlightedOption - 1, m_HighlightedOption + 1, m_LeftArrow, m_RightArrow);
        Navigate(key);
    }

    ToggleConsoleCursor(true);
}

void DynamicUi::Display(){
    size_t centeredText;
    size_t i = m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN_SPACING;
    std::string accept = "Accept";

    system(CLEAR);

    for (const auto& instruction : m_Instructions) {
        std::cout << instruction << std::endl;
    }

    for (const auto& menuOption : m_MenuOptions) {
        centeredText = m_Window.columns / 2 - menuOption.length() / 2;
        gotoxy(centeredText, i);
        i++;
        std::cout << menuOption;
    }

    centeredText = m_Window.columns / 2 - accept.length() / 2;
    if (!PrintAccept(centeredText, i)) {
        m_SelectionsSpace.lowerLimit = m_OptionCount + m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN_SPACING - 1;
    }
}

void DynamicUi::PrintLog() {
    int messageLine = GetSelectionsSpace().lowerLimit + UiSpacing::MESSAGE_LINE_SPACING;
    //Clear message line
    ClearLine(messageLine);

    //Print new message
    gotoxy((m_Window.columns / 2) - (m_Logger->GetLogString().length() / 2), messageLine); 
    m_Logger->PrintLog();
}

bool DynamicUi::PrintAccept(size_t x, size_t y){
    gotoxy(x, y);
    std::cout << "\x1b[32m" << "Accept" << "\033[0m";
    return true;
}

void DynamicUi::Navigate(const char key) {
    switch (key) {
        case keys::UP_KEY: {
            m_HighlightedOption++;
            if (m_HighlightedOption > m_SelectionsSpace.lowerLimit) {
                m_HighlightedOption = m_SelectionsSpace.upperLimit;
            }
            m_OptionIndex++;
            m_OptionIndex %= m_OptionCount + UiSpacing::ACCEPT_LINE_SPACING;
            break;
        }

        case keys::DOWN_KEY: {
            m_HighlightedOption--;
            if (m_HighlightedOption < m_SelectionsSpace.upperLimit) {
                m_HighlightedOption = m_SelectionsSpace.lowerLimit;
            }
            m_OptionIndex--;
            m_OptionIndex %= m_OptionCount + UiSpacing::ACCEPT_LINE_SPACING;
            break;
        }

        case keys::ENTER_KEY: {
            OnSelect();
            break;
        }

        case keys::BACKSPACE_KEY: {
            OnDeselect();
            break;
        }

        case keys::Q_KEY: {
            m_Logger->Log("Exiting Ui by cancelation", Logger::LogLevelInfo, Logger::LogFile);
            m_Terminate = true;
            m_ChangesMade = false;
            break;
        }
    }
}

//These two functions are to be completely built by the user
void DynamicUi::OnSelect() {
    return;
}

void DynamicUi::OnDeselect() {
    return;
}

void DynamicUi::Exit(bool changesMade) {
    m_ChangesMade = changesMade;

    if (m_ChangesMade) {
        m_Logger->Log("User exiting menu by accepting", Logger::LogLevelInfo, Logger::LogFile);
    } else {
        m_Logger->Log("User exiting menu by cancelling", Logger::LogLevelInfo, Logger::LogFile);
    }
    m_Terminate = true;
}

