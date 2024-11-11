#include "ui/SeasonMenu.h"

SeasonMenu::SeasonMenu() {
	m_Logger = std::make_shared<Logger>();
}

void SeasonMenu::InitializeSeasonMenu(std::shared_ptr<Logger> logger, std::shared_ptr<Season> season) {
	m_Logger = logger;
	m_Logger->Log("Initializing Season menu", Logger::LogLevelInfo, Logger::LogFile);
	m_Season = season;
	std::filesystem::path programDataPath = util::APP_DIRECTORY_DATA / util::PROGRAM_DATA;
	std::ifstream programDataFile(programDataPath);

	if (!programDataFile.is_open()) {
		m_Logger->Log("Could not open the program data file", Logger::LogLevelError, Logger::LogConsoleFile);
	}
	m_Logger->Log("Initialized season menu", Logger::LogLevelSuccess, Logger::LogFile);
	Menu();
}

void SeasonMenu::Menu() {
	std::vector<std::string> instructions = { "Season Menu", "Arrow keys: Move up and down", "Enter: select option", "Q: exit" };
	std::vector<std::string> menuOptions = { "Add Season", "Modify Season", "Delete Season", "Change Season", "Save Changes", "Exit"};
	
	SingleSelectionUi menu(m_Logger, instructions, menuOptions);

	int selection;
	bool changesMade = false;
	bool exit = false;

	do {
		menu.InitializeUi();
		if (menu.GetChangesMade()) {
			selection = menu.GetSelection();
			switch (selection) {
			case options::ADD_SEASON: {
				if (!changesMade) {
					changesMade = AddSeason();
				} else {
					AddSeason();
				}
				break;
			}

			case options::MODIFY_SEASON: {
				if (!changesMade) {
					changesMade = ModifySeason();
				} else {
					ModifySeason();
				}
				break;
			}

			case options::DELETE_SEASON: {
				if (!changesMade) {
					changesMade = DeleteSeason();
				} else {
					DeleteSeason();
				}
				break;
			}

			case options::CHANGE_SEASON: {
				ChangeSeason();
				break;
			}

			case options::SAVE_CHANGES_SEASON: {
				m_Logger->Log("User requested to save changes", Logger::LogLevelInfo, Logger::LogFile);
				if (changesMade) {
					
				} else {
					m_Logger->Log("No changes to save", Logger::LogLevelWarning, Logger::LogConsoleFile);
				}
				break;
			}
			case options::EXIT_SEASON: {
				exit = true;
				break;
			}

			default: {
				m_Logger->Log("Invalid option (" + std::to_string(selection + 1) + ")", Logger::LogLevelError, Logger::LogConsoleFile);
				break;
			}
			}
		}
	} while (menu.GetChangesMade() && !exit);
	
}

bool SeasonMenu::AddSeason() {
	return false;
}

bool SeasonMenu::ModifySeason() {
	system(CLEAR);
	std::cout << "Test finalizing season" << std::endl;
	util::ClearBuffer();
	util::EnterToContinue();
	m_Season->FinalizeSeason();
	return false;
}

bool SeasonMenu::DeleteSeason() {
	return false;
}

void SeasonMenu::ChangeSeason() {
}
