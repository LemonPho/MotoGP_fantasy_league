#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "core/Logger.h"
#include "models/Season.h"
#include "models/RiderManager.h"
#include "ui/DynamicUi/SingleSelectionUi.h"

class SeasonMenu {
public:
	enum options {
		ADD_SEASON = 0,
		MODIFY_SEASON,
		DELETE_SEASON,
		CHANGE_SEASON,
		SAVE_CHANGES_SEASON,
		EXIT_SEASON,
	};
private:
	std::shared_ptr<Logger> m_Logger;
	std::shared_ptr<Season> m_Season;
	std::vector<std::string> m_SeasonNameList;
public:
	SeasonMenu();

	void InitializeSeasonMenu(std::shared_ptr<Logger> logger, std::shared_ptr<Season> season);
	void Menu();

	bool AddSeason();
	bool ModifySeason();
	bool DeleteSeason();
	void ChangeSeason();
};