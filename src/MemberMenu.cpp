#include "MemberMenu.h"

MemberMenu::MemberMenu() {
    m_Logger = std::make_shared<Logger>();
}

MemberMenu::MemberMenu(std::shared_ptr<Logger> logger) {
    m_Logger = logger;
}

void MemberMenu::InitializeMemberMenu() {
    std::ifstream file(util::APP_DIRECTORY_DATA/util::PROGRAM_DATA);
    std::string tempString;

    if(!file.is_open()){
        m_Logger->Log("Could not open program data file", Logger::LogLevelError, Logger::LogConsoleFile);
    } else {
        std::getline(file, tempString, '\n');
        m_SelectedSeason = tempString;
    }

    m_RiderManagerList.ReadFromDisk(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::RIDER_DATA));
    m_MemberList.ReadFromDisk(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::MEMBER_DATA), m_RiderManagerList);

    Menu();
}

//Menu() shouldn't be called manually, call InitializeMemberMenu() instead
void MemberMenu::Menu() {
    bool end = false;
    bool saveChanges;
    std::string option;

    do {
        system(CLEAR);
        std::cout << "Member Menu, " << m_SelectedSeason << std::endl;
        m_Logger->PrintLog();
        std::cout << "1. Add Member" << std::endl;
        std::cout << "2. Delete Member" << std::endl;
        std::cout << "3. Modify Member" << std::endl;
        std::cout << "4. List Members" << std::endl;
        std::cout << "5. Delete ALL Members" << std::endl;
        std::cout << "6. Create standings file" << std::endl;
        std::cout << "7. Save Changes" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Option: ";
        std::cin >> option;
        switch(OptionSelector(option)){
            case INVALID_OPTION: {
                m_Logger->Log("Invalid option (" + option + ")", Logger::LogLevelError, Logger::LogConsoleFile);
                break;
            }
            case ADD_MEMBER: {
                m_Logger->Log("Opening add member", Logger::LogLevelInfo, Logger::LogFile);
                if(!saveChanges){
                    saveChanges = AddMember();
                } else {
                    AddMember();
                }
                break;
            }

            case DELETE_MEMBER: {
                m_Logger->Log("Opening delete member", Logger::LogLevelInfo, Logger::LogFile);
                if(!saveChanges){
                    saveChanges = DeleteMember();
                } else {
                    DeleteMember();
                }
                break;
            }

            case MODIFY_MEMBER: {
                m_Logger->Log("Opening modify member", Logger::LogLevelInfo, Logger::LogFile);
                if(!saveChanges){
                    saveChanges = ModifyMember();
                } else {
                    ModifyMember();
                }
                break;
            }

            case SHOW_MEMBERS: {
                m_Logger->Log("Displaying member list", Logger::LogLevelInfo, Logger::LogFile);
                system(CLEAR);
                std::cout << m_MemberList.ToString() << std::endl;
                std::cin.ignore();
                util::EnterToContinue();
                break;
            }

            case DELETE_ALL_MEMBERS: {
                char opt;
                std::cout << "Are you sure you want to delete all the members? (Y/N): ";
                std::cin >> opt;
                if(opt == 'Y' || opt == 'y'){
                    m_Logger->Log("Deleting all member", Logger::LogLevelInfo, Logger::LogFile);
                    m_MemberList.DeleteAllMembers();

                }
                util::EnterToContinue();
                saveChanges = true;
                break;
            }

            case CREATE_STANDINGS_FILE: {
                std::ofstream fileTXT(util::DOWNLOADS_DIRECTORY/"MotoGP fantasy standings.txt", std::ios::out);
                std::ofstream fileHTML(util::DOWNLOADS_DIRECTORY/"MotoGP fantasy standings.html", std::ios::out);

                if(!fileTXT.is_open() || !fileHTML.is_open()){
                    m_Logger->Log("One of the files couldn't be created in the downloads directory", Logger::LogLevelError, Logger::LogConsoleFile);
                } else {
                    m_Logger->Log("Standings file should be located in the downloads folder", Logger::LogLevelInfo, Logger::LogConsole);
                    m_Logger->Log("Standings files created", Logger::LogLevelSuccess, Logger::LogFile);
                }

            }

            case SAVE_CHANGES: {
                m_MemberList.WriteToDisk(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::MEMBER_DATA));
                saveChanges = false;
                break;
            }

            case EXIT: {
                end = true;
                break;
            }
        }
    }while(!end);
}

bool MemberMenu::AddMember() {
    int riderCount = m_RiderManagerList.GetRiderManagerList().size();

    return true;
}

bool MemberMenu::DeleteMember() {
    return false;
}

bool MemberMenu::ShowMembers() {
    return false;
}

bool MemberMenu::ModifyMember() {
    return false;
}

int MemberMenu::OptionSelector(const std::string &option) {
    if(option == "1") return ADD_MEMBER;
    if(option == "2") return DELETE_MEMBER;
    if(option == "3") return MODIFY_MEMBER;
    if(option == "4") return SHOW_MEMBERS;
    if(option == "5") return DELETE_ALL_MEMBERS;
    if(option == "6") return CREATE_STANDINGS_FILE;
    if(option == "7") return SAVE_CHANGES;
    if(option == "8") return EXIT;
    return 0;
}
