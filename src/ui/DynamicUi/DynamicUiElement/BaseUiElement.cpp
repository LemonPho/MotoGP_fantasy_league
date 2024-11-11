#include "ui/DynamicUi/DynamicUiElement/BaseUiElement.h"

BaseUiElement::BaseUiElement(std::shared_ptr<Logger> logger, std::string label, Positioning positioning, std::vector<std::string> contentArray) : 
	m_Logger(logger), m_Positioning(positioning), m_Label(label), m_ContentArray(contentArray) {

	size_t longestContentString = 0;

	for (auto& contentString : contentArray) {
		if (contentString.length() > longestContentString) {
			longestContentString = contentString.length();
		}
	}

	m_Coordinates.x = 0;
	m_Coordinates.y = 0;
	
	m_Size.height = 0;
	m_Size.width = 0;
}

BaseUiElement::Size BaseUiElement::GetSize() {
	return m_Size;
}

BaseUiElement::Coordinate BaseUiElement::GetCoordinates() {
	return m_Coordinates;
}

BaseUiElement::Positioning BaseUiElement::GetPositioning() {
	return m_Positioning;
}

int BaseUiElement::GetSelection() {
	return 0;
}

std::vector<int>& BaseUiElement::GetSelections() {
	return std::vector<int>();
}

BaseUiElement::SelectionType BaseUiElement::GetSelectionType() {
	return SelectionType::WRONG_USAGE;
}

void BaseUiElement::OnSelect() {
}

void BaseUiElement::OnDeselect() {
}
