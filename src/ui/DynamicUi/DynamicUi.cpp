#include "ui/DynamicUi/DynamicUi.h"

DynamicUi::DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions)
    : m_Logger(std::move(logger)), m_Instructions(instructions), m_MenuOptions(menuOptions)
{
    m_Selections.resize(m_MenuOptions.size(), false);
    m_InstructionsLength = m_Instructions.size();
    m_OptionCount = m_MenuOptions.size();
    m_HighlightedOption = m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN;
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

std::vector<bool>& DynamicUi::GetSelections() {
    return m_Selections;
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

void DynamicUi::InitializeUi() {
    m_Logger->Log("Starting dynamic ui", Logger::LogLevelInfo, Logger::LogFile);
    ToggleConsoleCursor(false);
    util::GetWindowDimensions(m_Window.columns, m_Window.rows);

    for (auto& menuOption : m_MenuOptions) {
        if (menuOption.length() > m_LongestMenuOption) {
            m_LongestMenuOption = menuOption.length();
        }
    }

    m_LeftArrow = (m_Window.columns / 2 - m_LongestMenuOption / 2) - UiSpacing::ARROWS;
    m_RightArrow = (m_Window.columns / 2 + m_LongestMenuOption / 2) + UiSpacing::ARROWS;
    char key;

    Display();
    while (!m_Terminate) {
        UpdateArrowPosition(m_HighlightedOption, m_LeftArrow, m_RightArrow);

        key = util::CustomGetch();
        ClearText(m_HighlightedOption - 1, m_HighlightedOption + 1, m_LeftArrow, m_RightArrow);
        Navigate(key);
    }

    ToggleConsoleCursor(true);
}

void DynamicUi::Display(){
    int centeredText;
    int i = m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN;
    std::string accept = "Accept";

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
    gotoxy(centeredText, i);
    std::cout << "\x1b[32m" << accept << "\033[0m";
}

void DynamicUi::Navigate(const char key) {
    switch (key) {
        case keys::UP_KEY: {
            m_HighlightedOption++;
            if (m_HighlightedOption > m_OptionCount + m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN) {
                m_HighlightedOption = m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN;
            }
            m_OptionIndex++;
            m_OptionIndex %= m_OptionCount + UiSpacing::ACCEPT;
            break;
        }

        case keys::DOWN_KEY: {
            m_HighlightedOption--;
            if (m_HighlightedOption < m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN) {
                m_HighlightedOption = m_OptionCount + m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN;
            }
            m_OptionIndex--;
            m_OptionIndex %= m_OptionCount + UiSpacing::ACCEPT;
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
            std::fill(m_Selections.begin(), m_Selections.end(), false);
            m_Terminate = true;
            break;
        }
    }
}

void DynamicUi::OnSelect() {
    if (m_HighlightedOption == m_OptionCount + m_InstructionsLength + UiSpacing::INSTRUCTIONS_DOWN) {
        Exit(true);
    }
    else {
        m_Logger->Log("Option: " + m_MenuOptions[m_OptionIndex] + " selected", Logger::LogLevelInfo, Logger::LogFile);
        int selectionPosition = (m_Window.columns / 2 + m_LongestMenuOption / 2 + UiSpacing::SELECT);
        gotoxy(selectionPosition, m_HighlightedOption);
        std::cout << "x";
        m_Selections[m_OptionIndex] = true;
    }
}

void DynamicUi::OnDeselect() {
    if (m_OptionIndex >= m_Selections.size()) {
        return;
    }

    m_Logger->Log("Option: " + m_MenuOptions[m_OptionIndex] + " removed from selections", Logger::LogLevelInfo, Logger::LogFile);
    int selectionPosition = (m_Window.columns / 2 + m_LongestMenuOption / 2 + UiSpacing::SELECT);
    gotoxy(selectionPosition, m_HighlightedOption);
    std::cout << " ";
    m_Selections[m_OptionIndex] = false;
}

void DynamicUi::Exit(bool changesMade) {
    m_ChangesMade = changesMade;

    if (m_ChangesMade) {
        m_Logger->Log("User exiting menu by accepting", Logger::LogLevelInfo, Logger::LogFile);
    }
    m_Terminate = true;
}

