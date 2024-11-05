#include "ui/DynamicUi/RidersSelectorUi.h"

RidersSelectorUi::RidersSelectorUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions) : DynamicUi(logger, instructions, menuOptions) {
    m_Logger = logger;
}

void RidersSelectorUi::PrintMessage(std::string message) {
    gotoxy(m_Window.columns - (message.length()/2), GetOptionCount() + GetInstructionsLength() + UiSpacing::INSTRUCTIONS_DOWN + RidersSelectorUiSpacing::MESSAGE_LINE_SPACING);
    std::cout << message;
}

void RidersSelectorUi::OnSelect() {
    if (GetHighlightedOption() == GetOptionCount() + GetInstructionsLength() + UiSpacing::INSTRUCTIONS_DOWN) {
        if (m_SelectionCount == Member::RIDER_COUNT) {
            Exit();
        } else {
            PrintMessage("You must select 6 riders");
            m_Logger->Log("User tried to save " + std::to_string(m_SelectionCount) + " riders, 6 required", Logger::LogLevelError, Logger::LogFile);
        }
        return;
    }
    

}

void RidersSelectorUi::OnDeselect() {

}