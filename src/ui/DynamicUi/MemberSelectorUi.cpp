#include "ui/DynamicUi/MemberSelectorUi.h"

MemberSelectorUi::MemberSelectorUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions) : DynamicUi(logger, instructions, menuOptions) {
	m_Logger = logger;
}

size_t MemberSelectorUi::GetSelections() {
	return m_Selections;
}

void MemberSelectorUi::OnSelect() {
	if (GetHighlightedOption() == GetAcceptLine()) {
		return;
	}

	m_Selections = GetOptionIndex();
	Exit(true);
}

void MemberSelectorUi::OnDeselect() {
	return;
}