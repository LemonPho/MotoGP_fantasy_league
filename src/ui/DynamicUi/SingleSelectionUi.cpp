/*
#include "ui/DynamicUi/SingleSelectionUi.h"

SingleSelectionUi::SingleSelectionUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions) : DynamicUi(logger, instructions, menuOptions) {
	m_Logger = logger;
}

int SingleSelectionUi::GetSelection() {
	return m_Selection;
}

bool SingleSelectionUi::PrintAccept(size_t x, size_t y) {
	return false;
}

void SingleSelectionUi::OnSelect() {
	m_Selection = GetOptionIndex();
	Exit(true);
}

void SingleSelectionUi::OnDeselect() {
	return;
}
*/