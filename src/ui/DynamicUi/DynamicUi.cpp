#include "ui/DynamicUi/DynamicUi.h"

DynamicUi::DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions)
    : m_Logger(std::move(logger)), m_Instructions(instructions), m_MenuOptions(menuOptions)
{
    m_Selections.reserve(m_MenuOptions.size());
    std::fill(m_Selections.begin(), m_Selections.end(), false);
    m_InstructionsLength = m_Instructions.size();
    m_OptionCount = m_MenuOptions.size();
}

void DynamicUi::gotoxy(size_t x, size_t y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

std::vector<bool>& DynamicUi::GetSelections() {
    return m_Selections;
}

void DynamicUi::StartUi() {
    m_Logger->Log("Starting dynamic ui", Logger::LogLevelInfo, Logger::LogFile);

    size_t leftArrow, rightArrow;

    Display();
    while (!m_Terminate) {

        util::ClearText(m_HighLightedOption + m_InstructionsLength + 1, m_HighLightedOption + m_InstructionsLength - 1, );
    }
}

void DynamicUi::Display(){
    for (const auto& menuOption : m_MenuOptions) {
        std::cout << std::endl;
        std::cout << "\t\t" << menuOption;
    }
}

void DynamicUi::Navigate(const char key) {
    switch (key) {
        case keys::UP_KEY: {
            m_HighLightedOption++;
            m_HighLightedOption %= m_OptionCount;
            break;
        }

        case keys::DOWN_KEY: {
            m_HighLightedOption--;
            m_HighLightedOption %= m_OptionCount;
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
            break;
        }
    }
}

void DynamicUi::OnSelect() {
    m_Logger->Log("Option: " + m_MenuOptions[m_HighLightedOption] + " selected", Logger::LogLevelInfo, Logger::LogFile);
    m_Selections[m_HighLightedOption] = true;
}

void DynamicUi::OnDeselect() {
    m_Logger->Log("Option: " + m_MenuOptions[m_HighLightedOption] + " removed from selections", Logger::LogLevelInfo, Logger::LogFile);
    m_Selections[m_HighLightedOption] = false;
}

