#pragma once
#ifndef MOTO_GP_FANTASY_LEAGUE_MODERN
#define MOTO_GP_FANTASY_LEAGUE_MODERN

#include "DynamicUi.h"
#include "models/Member.h"
#include "core/Logger.h"

class RidersSelectorUi : public DynamicUi {
private:
	std::shared_ptr<Logger> m_Logger;
	int m_Selections[Member::RIDER_COUNT] = {-1, -1, -1, -1, -1, -1};
	size_t m_SelectionCount = 0;

	int CheckIfSelected(size_t query);
	int GetEmptySpotSelections();
public:
	RidersSelectorUi(std::shared_ptr<Logger> logger, std::vector<std::string>& instructions, std::vector<std::string>& menuOptions);

	void PrintMessage(std::string message);

	int* GetSelections();

	void OnSelect() override;
	void OnDeselect() override;

	~RidersSelectorUi() override = default;
};

enum RidersSelectorUiSpacing {
	MESSAGE_LINE_SPACING = 1,
};

#endif 