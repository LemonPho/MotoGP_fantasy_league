#include "DynamicUi.h"

DynamicUi::DynamicUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions)
    : m_Logger(std::move(logger)), m_Instructions(instructions), m_MenuOptions(menuOptions){}


void DynamicUi::StartUi() {

}

void DynamicUi::Display(){
    for (const auto& menuOption : m_MenuOptions) {
        std::cout << std::endl;
        std::cout << "\t\t" << menuOption;
    }
}

