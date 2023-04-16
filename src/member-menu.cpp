#include "member-menu.h"
#include "menu.h"

MemberMenu::MemberMenu(MemberList *memberList, RiderList *riderList, string &seasonName) {
    this->memberList = memberList;
    this->riderList = riderList;
    this->seasonName = seasonName;
    saveChanges = false;
    updateMemberPoints();
    memberList->sortMembers();
    menu();
}

void MemberMenu::updateMemberPoints() {
    int totalPoints;
    MemberNode* tempMemberNode(memberList->getFirstPos());
    Member tempMember;
    Rider tempRookie;
    RiderNode* tempRiderNode = new RiderNode();

    while(tempMemberNode != nullptr){
        totalPoints = 0;
        tempMember = tempMemberNode->getData();
        tempRiderNode = tempMember.getRiderList()->getFirstPos();
        while(tempRiderNode != nullptr) {
            totalPoints += tempRiderNode->getData().getPoints();
            tempRiderNode = tempRiderNode->getNext();
        }
        tempMember.setPoints(totalPoints);
        tempMemberNode->setData(tempMember);
        tempMemberNode = tempMemberNode->getNext();
    }
}

void MemberMenu::menu() {
    bool end = false;
    int option;
    do{
        system(CLEAR);
        cout << "Member Menu, " << seasonName << endl;
        cout << "1. Add Member" << endl;
        cout << "2. Delete Member" << endl;
        cout << "3. Modify Member" << endl;
        cout << "4. List Members" << endl;
        cout << "5. Delete ALL Members" << endl;
        cout << "6. Create standings file" << endl;
        cout << "7. Save Changes" << endl;
        cout << "8. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case ADD_MEMBER: {
                saveChanges = addMember();
                updateMemberPoints();
                break;
            }
            case DELETE_MEMBER: {
                saveChanges = deleteMember();
                break;
            }
            case MODIFY_MEMBER: {
                modifyMember();
                updateMemberPoints();
                break;
            }
            case LIST_MEMBERS: {
                system(CLEAR);
                cout << memberList->toString() << endl;
                cin.ignore();
                enterToContinue();
                break;
            }
            case DELETE_ALL_MEMBERS: {
                char opt;
                cout << "Are you sure you want to continue? (S/N): ";
                cin >> opt;
                if(opt == 's' || opt == 'S'){
                    memberList->deleteAll();
                }
                enterToContinue();
                saveChanges = true;
                break;
            }
            case CREATE_STANDINGS_FILE: {
                system(CLEAR);

                //create current standings file (DOESN'T WORK, DONT KNOW WHY, JUST PRINTS RANDOM NUMBERS IN GROUPS OF 4)
                ofstream file(seasonName + '-' + CURRENT_STANDINGS, ios::out);
                if(!file.is_open()){
                    cout << "Standings file NOT created successfully, check if administrator privileges are necessary" << endl;
                } else {
                    file << memberList->toStringSmall() << endl << endl;
                    file.close();
                    cout << "Standings file created successfully" << endl;
                    cout << "To open file standings on macOS:" << endl;
                    cout << "Open Finder, on the top of the screen select Go, in the options select Home and the file should be labelled (season name)-current-standings.txt" << endl;
                    cout << "On windows it should be located in the same directory as the program" << endl;
                    getchar();
                    enterToContinue();
                }
            }
            case SAVE_CHANGES_MEMBER: {
                memberList->writeToDisk(seasonName + '-' + MEMBER_DATA);
                saveChanges = false;
                break;
            }
            case EXIT_MEMBER: {
                if(saveChanges) {
                    char opt;
                    cout << "Would you like to save the unsaved changes? (S/N)" << endl;
                    cout << "->";
                    cin >> opt;
                    if(opt == 's' || opt == 'S'){
                        memberList->writeToDisk(seasonName + '-' + MEMBER_DATA);
                    }
                }
                end = true;
                break;
            }
            default: {
                cout << "Select a valid option" << endl;
                enterToContinue();
                break;
            }
        }
    }while(!end);
}

bool MemberMenu::addMember() {
    Member tempMember;
    string userName;
    string riderListString;
    string usedNumbers[RIDER_COUNT] = {"-1","-1","-1","-1","-1"};
    Rider rookie;
    Rider tempRider;
    RiderNode* tempRiderNode;
    string tempRiderNumber;
    char option;

    system(CLEAR);
    cout << "Creating member" << endl;
    cout << "Input the user name" << endl;
    cout << "->";
    cin.ignore();getline(cin , userName);
    while(!tempMember.setUserName(userName)){
        cout << "Input a username less than 35 characters" << endl;
        cout << "->";
        getline(cin , userName);
    }

    riderListString = riderList->toString();
    cout << riderListString << endl;
    if(riderListString != "No riders in list"){
        for(int i = 0; i < RIDER_COUNT; i++){
            if(i == 5){
                cout << "Input the desired rider number (Independent Rider): " << endl;
                cout << "->";
                cin >> tempRiderNumber;
            } else {
                cout << "Input the desired rider number: " << endl;
                cout << "->";
                cin >> tempRiderNumber;
            }
            usedNumbers[i] = tempRiderNumber;
            tempRider.setNumber(tempRiderNumber);
            tempRiderNode = riderList->retrievePos(tempRider);
            tempRider = riderList->retrieveData(tempRiderNode);
            tempMember.insertRider(tempRider);
        }
    } else {
        cout << "Make sure after adding riders to add them to " << userName << endl;
        cin.ignore();
        enterToContinue();
    }
    memberList->insertData(memberList->getFirstPos(), tempMember);
    return true;
}

bool MemberMenu::deleteMember() {
    system(CLEAR);
    bool exit = false;
    string userName;
    Member tempMember;
    MemberNode* temp = new MemberNode();

    cout << "Delete Member" << endl;
    cout << memberList->toString() << endl;
    cout << "Input the member username to delete" << endl;
    cout << "-> ";
    cin.ignore();getline(cin, userName);
    tempMember.setUserName(userName);

    temp = memberList->retrievePos(tempMember);
    if(temp == nullptr){
        while(!exit || temp != nullptr) {
            cout << "Member not found, try again (0 to cancel)" << endl;
            cout << "-> ";
            getline(cin, userName);
            if(userName == "0"){
                exit = true;
            } else {
                tempMember.setUserName(userName);
                temp = memberList->retrievePos(tempMember);
            }
        }
    }
    if(exit){
        return false;
    }
    memberList->deleteData(temp);
    return true;
}

void MemberMenu::modifyMember() {
    system(CLEAR);
    bool exit = false;
    int option;
    bool changes = false;

    do {
        cout << "Modify Member" << endl;
        cout << "1. Change Username" << endl;
        cout << "2. Change Rider" << endl;
        cout << "3. Save Changes" << endl;
        cout << "4. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case CHANGE_USERNAME: {
                string userName;
                Member tempMember;
                MemberNode* tempNode(memberList->getFirstPos());
                bool endModify = false;
                system(CLEAR);
                cout << "Modify Member" << endl;

                cout << memberList->toString() << endl;
                cout << "Input the username of the member you would like to modify" << endl;
                cout << "-> ";
                cin.ignore();getline(cin, userName);
                tempNode = memberList->retrievePos(tempMember);

                while(!endModify && tempNode == nullptr){
                    cout << "Member not found, input again (0 to cancel)" << endl;
                    cout << "-> ";
                    getline(cin, userName);
                    if(userName == "0"){
                        endModify = true;
                    } else {
                        tempMember.setUserName(userName);
                        tempNode = memberList->retrievePos(tempMember);
                    }
                }

                if(endModify){
                    return;
                }

                cout << "Input the new username" << endl;
                cout << "-> ";
                getline(cin, userName);
                tempMember = tempNode->getData();
                tempMember.setUserName(userName);
                tempNode->setData(tempMember);
                changes = true;
                break;
            }
            case CHANGE_RIDER: {
                system(CLEAR);
                string userName;
                Member tempMember;
                MemberNode* tempMemberNode = new MemberNode();

                string riderNumber;
                Rider tempRider;
                RiderNode* tempRiderNode1 = new RiderNode();
                RiderNode* tempRiderNode2 = new RiderNode();

                bool endModify = false;
                system(CLEAR);
                cout << "Modify Member Rider" << endl;

                cout << memberList->toString() << endl;
                cout << "Input the username of the member's riders you would like to modify (0 to cancel)" << endl;
                cout << "-> ";
                cin.ignore();getline(cin, userName);
                tempMemberNode = memberList->retrievePos(tempMember);

                while(!endModify && tempMemberNode == nullptr){
                    cout << "Member not found, input again (0 to cancel)" << endl;
                    cout << "-> ";
                    getline(cin, userName);
                    if(userName == "0"){
                        endModify = true;
                    } else {
                        tempMember.setUserName(userName);
                        tempMemberNode = memberList->retrievePos(tempMember);
                    }
                }

                if(endModify){
                    return;
                }

                tempMember = tempMemberNode->getData();

                system(CLEAR);
                cout << "Modify Member Rider" << endl;
                cout << tempMember.getRiderList()->toString() << endl;
                cout << "Input rider number (0 to cancel)" << endl;
                cout << "-> ";
                getline(cin, riderNumber);
                tempRider.setNumber(riderNumber);
                tempRiderNode1 = tempMember.getRiderList()->retrievePos(tempRider);
                if(tempRiderNode1 == nullptr){
                    endModify = false;
                    while(tempRiderNode1 == nullptr && !endModify){
                        cout << "Rider not found, input number again (0 to cancel)" << endl;
                        cout << "-> ";
                        getline(cin, riderNumber);
                        if(riderNumber == "0"){
                            endModify = true;
                        } else {
                            tempRider.setNumber(riderNumber);
                            tempRiderNode1 = tempMember.getRiderList()->retrievePos(tempRider);
                        }
                    }
                    if(endModify){
                        return;
                    }
                }

                system(CLEAR);
                cout << "Modify Member Rider" << endl;
                cout << riderList->toString() << endl;
                cout << "Input new rider number (0 to cancel): " << endl;
                cout << "-> ";
                getline(cin, riderNumber);
                tempRider.setNumber(riderNumber);
                tempRiderNode2 = riderList->retrievePos(tempRider);
                if(tempRiderNode2 == nullptr){
                    endModify = false;
                    while(tempRiderNode2 == nullptr && !endModify){
                        cout << "Rider not found, input number again (0 to cancel)" << endl;
                        cout << "-> ";
                        getline(cin, riderNumber);
                        if(riderNumber == "0"){
                            endModify = true;
                        } else {
                            tempRider.setNumber(riderNumber);
                            tempRiderNode2 = riderList->retrievePos(tempRider);
                        }
                    }
                    if(endModify){
                        return;
                    }
                }

                tempRider = tempRiderNode2->getData();
                tempRiderNode1->setData(tempRider);

                changes = true;
                break;
            }
            case SAVE_CHANGES_MODIFY: {
                memberList->writeToDisk(seasonName + '-' + MEMBER_DATA);
                break;
            }
            case EXIT_MODIFY: {
                if(changes){
                    char opt;
                    cout << "Would you like to save the changes made? (S/N): ";
                    cin >> opt;
                    if(opt == 's' || opt == 'S'){
                        memberList->writeToDisk(seasonName + '-' + MEMBER_DATA);
                    }
                }
                exit = true;
                break;
            }
            default: {
                cout << "Choose a valid option" << endl;
                cin.ignore();
                enterToContinue();
                break;
            }
        }
    }while(!exit);

}

void MemberMenu::enterToContinue() {
    cout << "Press enter to continue" << endl;
    getchar();
}
