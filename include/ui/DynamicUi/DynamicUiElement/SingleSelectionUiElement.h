#pragma once

#include "BaseUiElement.h"
#include "core/Logger.h"

class SingleSelectionUiElement : public BaseUiElement {
private:
	std::shared_ptr<Logger> m_Logger;

	size_t m_Selection = 0;
	size_t m_OptionIndex = 0;
public:
	SingleSelectionUiElement(std::shared_ptr<Logger> logger, const std::string label, Positioning positioning, const std::vector<std::string>& contentArray);
	
	void InitializeUiElement(Window window, size_t y) override;

	int GetSelection() override;

	void RemoveHightlight(std::string& string, size_t y);
	void PrintHightlight(std::string& string, size_t y);

	void OnKeyUp() override;
	void OnKeyDown() override;
	void OnSelect() override;
};