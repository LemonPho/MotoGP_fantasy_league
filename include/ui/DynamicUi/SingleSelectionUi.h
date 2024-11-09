#pragma once

#include "ui/DynamicUi/DynamicUi.h"

class SingleSelectionUi : public DynamicUi {
private:
	std::shared_ptr<Logger> m_Logger;
	int m_Selection = -1;
public:
	SingleSelectionUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

	int GetSelection();

	bool PrintAccept(size_t x, size_t y) override;
	void OnSelect() override;
	void OnDeselect() override;
};