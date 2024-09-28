#include "DynamicUi.h"

DynamicUi::DynamicUi() {
    m_Logger = std::make_shared<Logger>();
}

DynamicUi::DynamicUi(std::shared_ptr<Logger> logger) {
    m_Logger = logger;
}

DynamicUi::DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions) {
    m_Logger = logger;
    m_Instructions = instructions;
    m_MenuOptions = menuOptions;
}
