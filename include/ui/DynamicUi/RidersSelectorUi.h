/*
#pragma once

#include "DynamicUi.h"
#include "models/Member.h"
#include "core/Logger.h"

class RidersSelectorUi : public DynamicUi {
private:
	std::shared_ptr<Logger> m_Logger;
	std::vector<int> m_Selections = { -1, -1, -1, -1, -1, -1 };
	size_t m_SelectionCount = 0;

	int CheckIfSelected(size_t query);
	int GetEmptySpotSelections();
public:
	RidersSelectorUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

	std::vector<int>& GetSelections();

	void OnSelect() override;
	void OnDeselect() override;

	~RidersSelectorUi() override = default;
};
*/