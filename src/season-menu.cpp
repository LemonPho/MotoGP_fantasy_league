#include "season-menu.h"

SeasonMenu::SeasonMenu(MemberList *memberList, RiderList *riderList, string &seasonName) {
    this->memberList = memberList;
    this->riderList = riderList;
    this->seasonName = seasonName;
    menu();
}

void SeasonMenu::menu() {
    bool end = false;
    int option;
    do{
        cout << "Season Menu: " << seasonName << endl;
        cout << "1. Create new season" << endl;
        cout << "2. Select season" << endl;
        cout << "3. Change default season" << endl;
        cout << "4. Exit" << endl;
        cin >> option;
        switch(option){
            case CREATE_SEASON: {
                createSeason();
                break;
            }
            case SELECT_SEASON: {
                changeSeason();
                break;
            }
            case CHANGE_DEFAULT_SEASON: {
                changeDefaultSeason();
                break;
            }
            case EXIT_SEASON: {
                end = true;
                break;
            }
            default: {
                cout << "Select a valid option" << endl;
                enterToContinue();
            }
        }
    }while(!end);
}

void SeasonMenu::createSeason() {
    system(CLEAR);

    string seasonName;
    string auxString;
    string seasons[100];
    int i = 1;
    bool finish = false;
    char option;
    fstream file(PROGRAM_DATA, ios::app | ios::in);

    getline(file, auxString);
    while (auxString != "") {
        seasons[i++] = auxString;
    }
    cout << "Creating season" << endl;
    cout << "Input the season name (change spaces for -): ";
    getline(cin, seasonName);
    while(!finish) {
        int j = 1;
        for(j; j < i; j++){
            if(seasons[j] == seasonName){
                cout << "Two seasons cant have the same name, input name again (0 to cancel): ";
                getline(cin, seasonName);
                if(seasonName == "0"){
                    return;
                }
                break;
            }
        }
        if(j == i){
            finish = true;
        }
    }
    cout << "Would you like to make it the default season? (S/N): ";
    cin >> option;
    ofstream file2(seasonName + '-' + MEMBER_DATA, ios::out);
    ofstream file3(seasonName + '-' + RIDER_DATA, ios::out);
    int j;
    if (option == 'S' || option == 's') {
        seasons[0] = seasonName;
        j = 0;
    } else {
        j = 1;
    }

    if (!file.is_open()) {
        cout << "Error couldn't open " << PROGRAM_DATA << endl;
        enterToContinue();
        return;
    } else {
        for (j; j < i; j++) {
            file << seasons[j] << endl;
        }
    }
    file.close();
    file2.close();
    file3.close();

}

void SeasonMenu::changeSeason() {
    system(CLEAR);

    string seasons[100];
    string auxString;
    bool validSelection = false;
    int selection;
    int i = 0;
    ifstream file(PROGRAM_DATA);

    getline(file, auxString);
    while(auxString != ""){
        seasons[i++] = auxString;
    }
    for(int j = 0; j < i; j++){
        cout << j+1 << " " << seasons[j] << endl;
    }
    cout << "Input the season number to select: ";
    cin >> selection;
    while(!validSelection){
        if(selection < 1 || selection > i){
            cout << "Select a valid season: ";
            cin >> selection;
        } else {
            validSelection = true;
        }
    }

    riderList = riderList->readFromDisk(seasons[selection-1] + '-' + RIDER_DATA);
    memberList = memberList->readFromDisk(seasons[selection-1] + '-' + MEMBER_DATA);

    MemberNode* tempMemberNode(memberList->getFirstPos());
    Member tempMember;
    Rider rider;
    string tempNumber;

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
            while(tempRider != nullptr){
                if(tempRider->getData() == rider){
                    rider = tempRider->getData();
                    tempMember.setRookie(rider);
                }
                tempRider = tempRider->getNext();
            }

        }
        tempMemberNode = tempMemberNode->getNext();
    }

}

void SeasonMenu::changeDefaultSeason() {
    system(CLEAR);

    string seasons[100];
    string auxString;
    bool validSelection = false;
    int selection;
    int i = 0;
    ifstream file(PROGRAM_DATA);

    getline(file, auxString);
    while(auxString != ""){
        seasons[i++] = auxString;
    }
    for(int j = 0; j < i; j++){
        cout << j+1 << " " << seasons[j] << endl;
    }
    cout << "Input the season number to select: ";
    cin >> selection;
    while(!validSelection){
        if(selection < 1 || selection > i){
            cout << "Select a valid season: ";
            cin >> selection;
        } else {
            validSelection = true;
        }
    }

    auxString = seasons[selection-1];
    seasons[selection-1] = seasons[0];
    seasons[0] = auxString;

    cout << "Restart the application to take effect" << endl;\
    enterToContinue();
}

void SeasonMenu::enterToContinue() {
    cout << "Press enter to continue" << endl;
    getchar();
}
