#include "ui/MemberMenu.h"

MemberMenu::MemberMenu() {
    m_Logger = std::make_shared<Logger>();
}

MemberMenu::MemberMenu(std::shared_ptr<Logger> logger) {
    m_Logger = logger;
}

void MemberMenu::InitializeMemberMenu() {
    m_Logger->Log("Initializing member menu", Logger::LogLevelInfo, Logger::LogFile);
    m_MemberList = MemberList(m_Logger);
    m_RiderManagerList = RiderManagerList(m_Logger);
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

    m_Logger->Log("Initialized member menu, starting menu", Logger::LogLevelInfo, Logger::LogFile);
    Menu();
}

//Menu() shouldn't be called, call InitializeMemberMenu() instead
void MemberMenu::Menu() {
    bool end = false;
    bool saveChanges = false;
    std::string option;

    m_MemberList.UpdateMembersPoints();
    m_MemberList.SortMembers();

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
                m_Logger->Log("Invalid option (" + option + ")", Logger::LogLevelError, Logger::LogConsole);
                break;
            }
            case ADD_MEMBER: {
                if(!saveChanges){
                    saveChanges = AddMember();
                } else {
                    AddMember();
                }

                m_MemberList.UpdateMembersPoints();
                m_MemberList.SortMembers();
                break;
            }

            case DELETE_MEMBER: {
                if(!saveChanges){
                    saveChanges = DeleteMember();
                } else {
                    DeleteMember();
                }

                m_MemberList.UpdateMembersPoints();
                m_MemberList.SortMembers();
                break;
            }

            case MODIFY_MEMBER: {
                if(!saveChanges){
                    saveChanges = ModifyMember();
                } else {
                    ModifyMember();
                }

                m_MemberList.UpdateMembersPoints();
                m_MemberList.SortMembers();
                break;
            }

            case SHOW_MEMBERS: {
                m_Logger->Log("Displaying member list", Logger::LogLevelInfo, Logger::LogFile);

                std::string memberListString = m_MemberList.ToString();
                if(!memberListString.empty()){
                    system(CLEAR);
                    std::cout << m_MemberList.ToString() << std::endl;
                    std::cin.ignore();
                    util::EnterToContinue();
                }

                break;
            }

            case DELETE_ALL_MEMBERS: {
                char opt;
                std::cout << "Are you sure you want to delete all the members? (Y/N): ";
                std::cin >> opt;
                if(opt == 'Y' || opt == 'y'){
                    m_Logger->Log("Deleting all member", Logger::LogLevelInfo, Logger::LogFile);
                    if(m_MemberList.DeleteAllMembers()){
                        saveChanges = true;
                    }
                }
                break;
            }

            case CREATE_STANDINGS_FILE: {
                m_MemberList.UpdateMembersPoints();
                m_MemberList.SortMembers();
                m_Logger->Log("Creating standings file", Logger::LogLevelInfo, Logger::LogFile);

                std::string tempString = m_MemberList.ToStringSmallHTML();

                if (tempString.empty()) {
                    m_Logger->Log("You need to have members saved to create a standings file", Logger::LogLevelError, Logger::LogConsole);
                    m_Logger->Log("Member list was empty when standings file was requested", Logger::LogLevelError, Logger::LogFile);
                } else {
                    std::ofstream fileTXT(util::DOWNLOADS_DIRECTORY / "MotoGP fantasy standings.txt", std::ios::out);
                    std::ofstream fileHTML(util::DOWNLOADS_DIRECTORY / "MotoGP fantasy standings.html", std::ios::out);

                    if (!fileTXT.is_open() || !fileHTML.is_open()) {
                        m_Logger->Log("One of the files couldn't be created in the downloads directory",
                            Logger::LogLevelError, Logger::LogConsoleFile);
                    } else {
                        fileTXT << tempString << std::endl;
                        fileHTML << tempString << std::endl;
                        fileHTML.close();
                        fileTXT.close();
                        m_Logger->Log("Standings file should be located in the downloads folder", Logger::LogLevelInfo, Logger::LogConsole);
                        m_Logger->Log("Standings files created", Logger::LogLevelSuccess, Logger::LogFile);
                    }
                }
                break;
            }

            case SAVE_CHANGES: {
                m_Logger->Log("Saving changes", Logger::LogLevelInfo, Logger::LogFile);
                if(!saveChanges){
                    m_Logger->Log("No changes have been registered", Logger::LogLevelInfo, Logger::LogConsoleFile);
                } else {
                    m_MemberList.WriteToDisk(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::MEMBER_DATA));
                    saveChanges = false;
                }
                break;
            }

            case EXIT: {
                if(saveChanges){
                    char opt;
                    std::cout << "Would you like to save the changes made? (Y/N): ";
                    std::cin >> opt;
                    if(opt == 'y' || opt == 'Y'){
                        m_Logger->Log("User exiting member menu and saving changes", Logger::LogLevelInfo, Logger::LogFile);
                        m_MemberList.WriteToDisk(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::MEMBER_DATA));
                    } else {
                        m_Logger->Log("User exiting member menu without saving changes", Logger::LogLevelInfo, Logger::LogFile);
                    }
                }
                end = true;
                break;
            }
        };
    }while(!end);
}

bool MemberMenu::AddMember() {
    m_Logger->Log("Opening add member", Logger::LogLevelInfo, Logger::LogFile);
    if(m_RiderManagerList.GetRiderManagerList().empty() || m_RiderManagerList.GetRiderManagerList().size() < 6){
        m_Logger->Log("You have no riders added, make sure to have 6 riders before creating a member", Logger::LogLevelError, Logger::LogConsole);
        m_Logger->Log("No riders in rider list", Logger::LogLevelError, Logger::LogFile);
        return false;
    }

    system(CLEAR);
    std::cout << "Before continuing, make sure the application is full screen" << std::endl;
    std::cout << "If when selecting riders, its all over the place, you can quit pressing q and make the text smaller pressing ctrl and -" << std::endl;
    util::ClearBuffer();
    util::EnterToContinue();
    system(CLEAR);

    //data
    std::string userName;
    int *selections; 
    RiderManager tempRiderManager(m_Logger);
    Member tempMember(m_Logger);

    m_Logger->Log("Receiving username", Logger::LogLevelInfo, Logger::LogFile);
    std::cout << "Creating Member" << std::endl;
    std::cout << "Input a user name: ";
    std::getline(std::cin, userName);
    while (!tempMember.SetUserName(userName)) {
        m_Logger->Log("User tried username: " + userName + ", too long", Logger::LogLevelError, Logger::LogFile);
        std::cout << "Input a username less than " + std::to_string(Member::MAX_USERNAME) + " characters" << std::endl;
        std::cout << "-> ";
        std::getline(std::cin, userName);
    }

    system(CLEAR);

    std::vector<std::string> instructions = { "Creating Member", "Add the member's picks", "Arrow keys for going up and down", "Enter: Select rider", "Backspace: Remove selected rider", "Q: cancel" };
    std::vector<std::string> options = m_RiderManagerList.ToStringVector();

    RidersSelectorUi ridersSelector(m_Logger, instructions, options);
    ridersSelector.InitializeUi();
    //check if operation was cancelled
    if (!ridersSelector.GetChangesMade()) {
        return false;
    }

    selections = ridersSelector.GetSelections();

    m_Logger->Log("Retreiving rider data from selections", Logger::LogLevelInfo, Logger::LogFile);
    for(size_t i = 0; i < Member::RIDER_COUNT; i++){
        tempRiderManager = m_RiderManagerList.GetRiderManagerIndex(selections[i]);
        tempRiderManager.SetPosition(i+1);
        tempMember.InsertRiderManager(tempRiderManager);
    }

    m_MemberList.AddMember(tempMember);
    m_Logger->Log("New member created with username: " + tempMember.GetMemberUserName(), Logger::LogLevelSuccess, Logger::LogFile);
    m_Logger->Log(tempMember.GetMemberUserName() + " created!", Logger::LogLevelSuccess, Logger::LogConsole);

    return true;
}

bool MemberMenu::DeleteMember() {
    m_Logger->Log("Opening delete member", Logger::LogLevelInfo, Logger::LogFile);
    
    if(m_MemberList.GetMemberList().empty()){
        m_Logger->Log("You have no members added", Logger::LogLevelWarning, Logger::LogConsole);
        m_Logger->Log("Members list empty, returning to member menu", Logger::LogLevelWarning, Logger::LogFile);
        return false;
    }

    system(CLEAR);
    
    std::vector<std::string> memberListString = m_MemberList.ToStringArray();
    std::vector<std::string> instructions = { "Delete member", "Select the members you would like to delete", "Arrow keys for going up and down", "Enter: Select member", "Backspace: Remove selected member", "Q: cancel" };
    std::vector<bool> selections;
    selections.resize(memberListString.size());

    DynamicUi deleteMemberUi(m_Logger, instructions, memberListString);

    deleteMemberUi.InitializeUi();

    //check if changes were made
    if (!deleteMemberUi.GetChangesMade()) {
        return false;
    }

    selections = deleteMemberUi.GetSelections();

    for(size_t i = 0; i < selections.size(); i++){
        if(selections[i]){
            Member tempMember(m_Logger);
            //instance only needs username, since it is used for comparison
            tempMember.SetUserName(m_MemberList.GetMemberList()[i].GetMemberUserName());
            m_MemberList.RemoveMember(tempMember);
        }
    }

    return true;
}

bool MemberMenu::ModifyMember() {
    m_Logger->Log("Opening modify member", Logger::LogLevelInfo, Logger::LogFile);
    if(m_MemberList.GetMemberList().empty()){
        m_Logger->Log("You have no members added", Logger::LogLevelWarning, Logger::LogConsole);
        m_Logger->Log("Member list empty, returning to member menu", Logger::LogLevelWarning, Logger::LogFile);
        return false;
    }

    std::vector<std::string> memberListInstructions = {"Modify Member", "Select the member you would like to modify", "Arrow keys for going up and down", "Enter: Select member", "Q: Cancel"};
    std::vector<std::string> memberListString = m_MemberList.ToStringArray();
    size_t memberSelection;

    system(CLEAR);
    MemberSelectorUi memberSelectorUi(m_Logger, memberListInstructions, memberListString);
    memberSelectorUi.InitializeUi();

    if (!memberSelectorUi.GetChangesMade()) {
        return false;
    }

    memberSelection = memberSelectorUi.GetSelections();

    Member tempMember = m_MemberList.GetMemberList()[memberSelection];

    std::vector<std::string> memberDetailString = tempMember.ToStringEdit();
    std::vector<std::string> memberDetailInstructions = { "Modify Member", "Select the attribute you would like to modify", "Arrow keys for going up and down", "Enter: Select attribute", "Q: Cancel" };
    size_t attributeSelection;

    system(CLEAR);
    MemberSelectorUi memberAttributeSelectorUi(m_Logger, memberDetailInstructions, memberDetailString);
    memberAttributeSelectorUi.InitializeUi();

    if (!memberSelectorUi.GetChangesMade()) {
        return false;
    }

    system(CLEAR);
    util::ClearBuffer();
    std::cout << "Modify Member" << std::endl;
    attributeSelection = memberAttributeSelectorUi.GetSelections();
    if (attributeSelection == Member::AttributesIndexed::USERNAME_INDEX) {
        std::string newUsername;
        std::cout << "Input the new username: " << std::endl;
        std::cout << "-> ";
        std::getline(std::cin, newUsername);

        while (!tempMember.SetUserName(newUsername)) {
            m_Logger->Log("User tried username: " + newUsername + ", too long", Logger::LogLevelError, Logger::LogFile);
            std::cout << "Input a username less than " + std::to_string(Member::MAX_USERNAME) + " characters" << std::endl;
            std::cout << "-> ";
            std::getline(std::cin, newUsername);
        }
    } else if (attributeSelection == Member::AttributesIndexed::RIDER_LIST_INDEX) {
        std::vector<std::string> oldRiderSelectionInstructions = { "Select the rider you would like to swap", "Arrow keys for going up and down", "Enter: Select rider", "Q: Cancel" };
        std::vector<std::string> oldRiderStringList = tempMember.GetRiderList().ToStringVector();
        size_t oldRiderSelection;
        RiderManager oldRider;

        MemberSelectorUi oldRiderSelectorUi(m_Logger, oldRiderSelectionInstructions, oldRiderStringList);
        oldRiderSelectorUi.InitializeUi();

        if (!oldRiderSelectorUi.GetChangesMade()) {
            return false;
        }
        oldRiderSelection = oldRiderSelectorUi.GetSelections();
        oldRider = tempMember.GetRiderList().GetRiderManagerList()[oldRiderSelection];

        std::vector<std::string> newRiderSelectionInstructions = { "Select the rider you would like to swap", "Arrow keys for going up and down", "Enter: Select rider", "Q: Cancel" };
        std::vector<std::string> newRiderStringList = m_RiderManagerList.ToStringVector();
        size_t newRiderSelection;

        system(CLEAR);
        MemberSelectorUi newRiderSelectorUi(m_Logger, newRiderSelectionInstructions, newRiderStringList);
        newRiderSelectorUi.InitializeUi();

        if (!newRiderSelectorUi.GetChangesMade()) {
            return false;
        }
        newRiderSelection = newRiderSelectorUi.GetSelections();

        if (tempMember.SetRiderManager(m_RiderManagerList.GetRiderManagerList()[newRiderSelection], oldRiderSelection)) {
            m_MemberList.SetMember(tempMember, memberSelection);
            m_Logger->Log("User changed " + m_MemberList.GetMemberList()[memberSelection].GetMemberUserName() + "'s pick from " + oldRider.ToStringSmall(false) + " to " + m_MemberList.GetMemberList()[memberSelection].GetRiderList().GetRiderManagerList()[oldRiderSelection].ToStringSmall(false), Logger::LogLevelSuccess, Logger::LogFile);
        }
    }

    m_Logger->Log("Changes successfully made", Logger::LogLevelSuccess, Logger::LogConsoleFile);

    return true;
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
