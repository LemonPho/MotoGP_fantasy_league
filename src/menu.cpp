#include "menu.h"
#include "util.h"

Menu::Menu() {
    system(CLEAR);
    ifstream file(PROGRAM_DATA);
    memberErrorMessage = ErrorMessage();
    memberList = new MemberList(nullptr, &memberErrorMessage);
    riderList = new RiderList(nullptr, &riderErrorMessage);

    //if the file exists, we start program normally
    if(file.is_open()){
        startProgram();
        menu();
    //if the file doesn't exist, we create it in firstStart()
    } else {
        firstStart();
        menu();
    }
}

void Menu::firstStart() {
    //create a new season since programdata is empty in this case
    ofstream file(PROGRAM_DATA, ios::out);

    cout << "Wellcome to the MotoGP Fantasy League Manager" << endl;
    cout << "Input a name for the current season (replace spaces with: - ): ";
    getline(cin, seasonName);

    //create member and rider data
    ofstream file2(seasonName + '-' + MEMBER_DATA, ios::out);
    ofstream file3(seasonName + '-' + RIDER_DATA, ios::out);
    file << seasonName << endl;

    //close the three files to save the changes
    file.close();
    file2.close();
    file3.close();
}

void Menu::startProgram() {
    ifstream file(PROGRAM_DATA);

    //get season name
    if(!file.is_open()){
        cout << "Error when opening " << PROGRAM_DATA << endl;
        throw exception();
    }
    getline(file, seasonName);
    //open data files for riders and members
    riderList = riderList->copyFromDisk(seasonName + '-' + RIDER_DATA);
    riderList->generatePositions();
    memberList = memberList->copyFromDisk(seasonName + '-' + MEMBER_DATA);
    memberList->retrieveMemberPicks(riderList);
}

//main menu
void Menu::menu() {
    bool end = false;
    string option;
    do{
        //main menu options
        system(CLEAR);
        cout << "MotoGP Fantasy League Manager. Current season: " << seasonName <<  endl;
        cout << "1. Seasons Manager" << endl;
        cout << "2. Members Manager" << endl;
        cout << "3. Riders Manager" << endl;
        cout << "4. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(optionSelector(option)){
            case SEASONS_MANAGER: {
                new SeasonMenu(memberList, riderList, &seasonName);
                memberList->modifyFromDisk(seasonName + '-' + MEMBER_DATA);
                riderList->modifyFromDisk(seasonName + '-' + RIDER_DATA);
                memberList->retrieveMemberPicks(riderList);
                break;
            }
            case MEMBERS_MANAGER: {
                new MemberMenu(memberList, riderList, seasonName, &memberErrorMessage);
                memberList->modifyFromDisk(seasonName + '-' + MEMBER_DATA);
                riderList->modifyFromDisk(seasonName + '-' + RIDER_DATA);
                memberList->retrieveMemberPicks(riderList);
                break;
            }
            case RIDERS_MANAGER: {
                new RiderMenu(memberList, riderList, seasonName, &riderErrorMessage);
                memberList->modifyFromDisk(seasonName + '-' + MEMBER_DATA);
                riderList->modifyFromDisk(seasonName + '-' + RIDER_DATA);
                memberList->retrieveMemberPicks(riderList);
                break;
            }
            case EXIT_MENU: {
                exit();
                end = true;
                break;
            }
            default: {
                cout << "Select a valid option" << endl;
                cin.ignore();
                enterToContinue();
            }
        }
    }while(!end);
}

void Menu::exit() {
   delete memberList;
   delete riderList;
}

int Menu::optionSelector(std::string option) {
    if(option == "1") return SEASONS_MANAGER;
    if(option == "2") return MEMBERS_MANAGER;
    if(option == "3") return RIDERS_MANAGER;
    if(option == "4") return EXIT_MENU;
    return 0;
}