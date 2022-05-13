#include "menu.h"

Menu::Menu() {
    system(CLEAR);
    ifstream file(PROGRAM_DATA);
    memberList = new MemberList();
    riderList = new RiderList();

    if(file.is_open()){
        startProgram();
        menu();
    } else {
        firstStart();
        menu();
    }
}

void Menu::firstStart() {
    ofstream file(PROGRAM_DATA, ios::out);

    cout << "Wellcome to the MotoGP Fantasy League Manager" << endl;
    cout << "Input a name for the current season (replace spaces with: - ): ";
    getline(cin, seasonName);

    ofstream file2(seasonName + '-' + MEMBER_DATA, ios::out);
    ofstream file3(seasonName + '-' + RIDER_DATA, ios::out);

    file << seasonName;
    file.close();
    file2.close();
    file3.close();
}

void Menu::startProgram() {
    ifstream file(PROGRAM_DATA);

    if(!file.is_open()){
        cout << "Error when opening " << PROGRAM_DATA << endl;
        throw exception();
    }
    getline(file, seasonName);
    riderList = riderList->readFromDisk(seasonName + '-' + RIDER_DATA);
    memberList = memberList->readFromDisk(seasonName + '-' + MEMBER_DATA);

    MemberNode* tempMemberNode(memberList->getFirstPos());
    Member tempMember;
    Rider rider;
    string tempNumber;
    bool found;

    while(tempMemberNode != nullptr){
        tempMember = tempMemberNode->getData();
        RiderNode* tempRiderNode1(tempMember.getRiderList()->getFirstPos());
        while(tempRiderNode1 != nullptr){
            RiderNode* tempRiderNode2(riderList->getFirstPos());
            tempNumber = tempRiderNode1->getData().getNumber();
            rider.setNumber(tempNumber);
            while(tempRiderNode2 != nullptr){
                if(tempRiderNode2->getData() == rider){
                    rider = tempRiderNode2->getData();
                    tempRiderNode1->setData(rider);
                }
                tempRiderNode2 = tempRiderNode2->getNext();
            }
            tempRiderNode1 = tempRiderNode1->getNext();
        }
        if(tempMember.getRookie().getNumber() != "-1"){
            RiderNode* tempRider(riderList->getFirstPos());
            tempNumber = tempMember.getRookie().getNumber();
            rider.setNumber(tempNumber);
            found = false;
            while(tempRider != nullptr){
                if(tempRider->getData() == rider){
                    rider = tempRider->getData();
                    tempMember.setRookie(rider);
                    found = true;
                }
                tempRider = tempRider->getNext();
            }

        }
        tempMemberNode = tempMemberNode->getNext();
    }
}

void Menu::menu() {
    bool end = false;
    int option;
    do{
        system(CLEAR);
        cout << "MotoGP Fantasy League Manager. Current season: " << seasonName <<  endl;
        cout << "1. Seasons Manager" << endl;
        cout << "2. Members Manager" << endl;
        cout << "3. Riders Manager" << endl;
        cout << "4. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case SEASONS_MANAGER: {
                new SeasonMenu(memberList, riderList, seasonName);
                break;
            }
            case MEMBERS_MANAGER: {
                new MemberMenu(memberList, riderList, seasonName);
                break;
            }
            case RIDERS_MANAGER: {
                new RiderMenu(riderList, seasonName);
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
    ofstream file(seasonName + '-' + CURRENT_STANDINGS, ios::out);
    file << memberList->toString() << endl;
    file.close();
}

void Menu::enterToContinue() {
    cout << "Press enter to continue..." << endl;
    getchar();
}
