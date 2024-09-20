#include "MemberMenu.h"

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

//Menu() shouldn't be called manually, call InitializeMemberMenu() instead
void MemberMenu::Menu() {
    bool end = false;
    bool saveChanges;
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
                m_Logger->Log("Invalid option (" + option + ")", Logger::LogLevelError, Logger::LogConsoleFile);
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
                m_Logger->Log("Opening delete member", Logger::LogLevelInfo, Logger::LogFile);
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
                m_Logger->Log("Opening modify member", Logger::LogLevelInfo, Logger::LogFile);
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
                saveChanges = true;
                break;
            }

            case CREATE_STANDINGS_FILE: {
                m_MemberList.UpdateMembersPoints();
                m_MemberList.SortMembers();
                m_Logger->Log("Creating standings file", Logger::LogLevelInfo, Logger::LogFile);
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
                m_Logger->Log("Exiting member menu", Logger::LogLevelInfo, Logger::LogFile);
                if(saveChanges){
                    char opt;
                    std::cout << "Would you like to save the changes made? (Y/N): ";
                    std::cin >> opt;
                    if(opt == 'y' || opt == 'Y'){
                        m_MemberList.WriteToDisk(util::APP_DIRECTORY_DATA/(m_SelectedSeason + util::MEMBER_DATA));
                    }
                }
                end = true;
                break;
            }
        }
    }while(!end);
}

bool MemberMenu::AddMember() {
    m_Logger->Log("Opening add member", Logger::LogLevelInfo, Logger::LogFile);
    //rider count
    size_t riderCount = m_RiderManagerList.GetRiderManagerList().size();
    //temporary data types
    Member tempMember;
    std::string userName, tempRiderNumber;
    Rider tempIndependent, tempRider;
    RiderManager tempRiderManager;
    //array of riders in string format
    std::vector<std::string> riderStringArray = m_RiderManagerList.ToStringVector();

    //array to save the selected riders by the user
    int selections[Member::RIDER_COUNT] = {-1, -1, -1, -1, -1, -1};
    //amount of riders selected
    int amountSelected=0;
    //option to keep track of what rider is being highlighted
    //lineOption is used to keep track of what line is being selected, since there is spacing in the top for info on how to use
    int option = 1, lineOption;
    //key inputted
    int key;
    bool exit = false;

    //spacing for ui elements
    //use longestStringLength to know how far to put the right arrow
    size_t longestStringLength = 0;
    for(const auto& riderString : riderStringArray){
        if(riderString.length() > longestStringLength){
            longestStringLength = riderString.length();
        }
    }
    //positioning for left and right arrow
    size_t leftArrow = LEFT_ARROW_SPACING, rightArrow = RIGHT_ARROW_SPACING + longestStringLength;
    //line where messages go
    size_t messageLine = MESSAGE_LINE_SPACING + riderCount;
    //column where messages start
    size_t messageStart = MESSAGE_START_SPACING;
    //line where accept is located
    size_t acceptLine = ACCEPT_LINE_SPACING + riderCount;

    system(CLEAR);

    std::cout << "Before continuing, make sure the application is full screen" << std::endl;
    std::cout << "If when selecting riders, its all over the place, you can quit pressing q and make the text smaller pressing ctrl and -" << std::endl;
    util::ClearBuffer();
    util::EnterToContinue();

    system(CLEAR);

    m_Logger->Log("Receiving username", Logger::LogLevelInfo, Logger::LogFile);
    std::cout << "Creating Member" << std::endl;
    std::cout << "Input a user name: ";
    std::getline(std::cin, userName);
    while(!tempMember.SetUserName(userName)){
        m_Logger->Log("User tried username: " + userName = ", too long", Logger::LogLevelError, Logger::LogFile);
        std::cout << "Input a username less than " + std::to_string(Member::MAX_USERNAME) + " characters" << std::endl;
        std::cout << "-> ";
        std::getline(std::cin, userName);
    }

    m_Logger->Log("Starting rider selector", Logger::LogLevelInfo, Logger::LogFile);
    system(CLEAR);
    std::cout << "Creating Member" << std::endl;
    std::cout << "Add the member's picks" << std::endl;
    std::cout << "Enter: add to list" << std::endl;
    std::cout << "Backspace: remove from list" << std::endl;
    std::cout << "q: return to member menu" << std::endl;

    util::PrintMenu(riderStringArray);
    std::cout << std::endl << "\t\t\x1b[32mAccept\033[0m" << std::endl;

    while(!exit){
        lineOption = option + LINE_OPTION_SPACING;

        util::UpdateArrowPosition(lineOption, leftArrow, rightArrow);
        key = util::CustomGetch();

        switch(key){
            case UP_KEY: {
                if(option == riderCount+1){
                    option = 1;
                } else {
                    option++;
                }
                break;
            }

            case DOWN_KEY:{
                if(option == 1){
                    option = riderCount+1;
                } else {
                    option--;
                }
                break;
            }

            case ENTER_KEY: {
                util::gotoxy(messageStart, messageLine);
                std::cout << "                                                     ";

                if(option == acceptLine){
                    if(amountSelected >= Member::RIDER_COUNT){
                        m_Logger->Log("Riders selected and saved", Logger::LogLevelInfo, Logger::LogFile);
                        exit = true;
                    } else {
                        util::gotoxy(messageStart, messageLine);
                        std::cout << "You must only select 6 riders" << std::endl;
                    }
                    break;
                }

                if(amountSelected == 4){
                    util::gotoxy(messageStart, messageLine);
                    std::cout << "The next rider will be the independent rider";
                }

                if(amountSelected >= Member::RIDER_COUNT){
                    util::gotoxy(messageStart, messageLine);
                    std::cout << "You have selected the max amount of riders";
                    break;
                }
                if(option != acceptLine && util::CheckIfSelected(selections, Member::RIDER_COUNT, option-1) == -1){
                    int i = 0;
                    for(i; i < Member::RIDER_COUNT; i++){
                        if(selections[i] == -1){
                            break;
                        }
                    }
                    if(i >= Member::RIDER_COUNT){
                        i = 5;
                    }
                    selections[i] = option-1;
                    util::gotoxy(rightArrow + 5, option + 6);
                    if(i == 5){
                        std::cout << "i";
                    } else {
                        std::cout << i+1;
                    }
                    m_Logger->Log("Selected rider", Logger::LogLevelInfo, Logger::LogFile);
                    amountSelected++;
                    break;
                }

                break;
            }

            case BACKSPACE_KEY: {
                int selected;

                util::gotoxy(messageStart, messageLine);
                std::cout << "                                                     ";

                selected = util::CheckIfSelected(selections, Member::RIDER_COUNT, option-1);
                if(selected != -1){
                    m_Logger->Log("Removed rider", Logger::LogLevelInfo, Logger::LogFile);
                    selections[selected] = -1;
                    util::gotoxy(rightArrow+5, option+6);
                    std::cout << " ";
                    amountSelected--;
                }
                break;
            }

            case Q_KEY: {
                return false;
            }
        }

        util::ClearText(lineOption-1, lineOption+1, leftArrow, rightArrow);
    }

    std::cout << std::endl;

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
