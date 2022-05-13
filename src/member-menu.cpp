#include "member-menu.h"
#include "menu.h"

MemberMenu::MemberMenu(MemberList *memberList, RiderList *riderList, string &seasonName) {
    this->memberList = memberList;
    this->riderList = riderList;
    this->seasonName = seasonName;
    saveChanges = false;
    updateMemberPoints();
    menu();
}

void MemberMenu::updateMemberPoints() {
    int totalPoints = 0;
    MemberNode* tempMemberNode(memberList->getFirstPos());
    Member *tempMember = new Member();

    while(tempMemberNode != nullptr){
        *tempMember = tempMemberNode->getData();
        RiderNode* tempRiderNode(tempMember->getRiderList()->getFirstPos());
        totalPoints = 0;
        while(tempRiderNode != nullptr){
            totalPoints += tempRiderNode->getData().getPoints();
            tempRiderNode = tempRiderNode->getNext();
        }
        totalPoints += tempMember->getPoints();
        tempMember->setPoints(totalPoints);
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
        cout << "6. Save Changes" << endl;
        cout << "7. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case ADD_MEMBER: {
                addMember();
                updateMemberPoints();
                saveChanges = true;
                break;
            }
            case DELETE_MEMBER: {
                deleteMember();
                saveChanges = true;
                break;
            }
            case MODIFY_MEMBER: {
                modifyMember();
                updateMemberPoints();
                saveChanges = true;
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
            case SAVE_CHANGES_MEMBER: {
                memberList->writeToDisk(seasonName + '-' + MEMBER_DATA);                break;
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

void MemberMenu::addMember() {
    Member tempMember;
    string userName;
    string riderListString;
    string usedNumbers[RIDER_COUNT] = {"-1","-1","-1","-1","-1"};
    Rider rookie;
    Rider tempRider;
    RiderNode* tempRiderNode;
    string tempRiderNumber;
    int riderCount = -1;
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

    while(riderCount <= -1 || riderCount >= 6){
        cout << "Input the amount of riders " << userName << " has chosen (0-5), you can add them later" << endl;
        cout << "->";
        cin >> riderCount;
        cin.ignore();
    }
    riderListString = riderList->toString();
    cout << riderListString << endl;
    if(riderListString != "No riders in list"){
        for(int i = 0; i < riderCount; i++){
            cout << "Input the desired rider number: " << endl;
            cout << "->";
            cin >> tempRiderNumber;
            for(int j = 0; j < i; j++){
                if(usedNumbers[j] == tempRiderNumber){
                    cout << "Make sure to not repeat the same riders" << endl;
                    cout << "Input a different number: " << endl;
                    cout << "->";
                    cin >> tempRiderNumber;
                    j = 0;
                }
            }
            usedNumbers[i] = tempRiderNumber;
            tempRider.setNumber(tempRiderNumber);
            tempRiderNode = riderList->retrievePos(tempRider);
            tempRider = riderList->retrieveData(tempRiderNode);
            tempMember.insertRider(tempRider);
        }
        cout << "Would you like to add a rookie? (S/N)" << endl;
        cout << "->";
        cin >> option;
        if(option == 's' || option == 'S'){
            cout << "Input the desired rider number" << endl;
            cout << "->";
            cin >> tempRiderNumber;
            tempRider.setNumber(tempRiderNumber);
            tempRiderNode = riderList->retrievePos(tempRider);
            rookie = riderList->retrieveData(tempRiderNode);
            while(!rookie.getRookie()){
                cout << "Please input a valid rookie (R)" << endl;
                cout << "->";
                cin >> tempRiderNumber;
                tempRider.setNumber(tempRiderNumber);
                tempRiderNode = riderList->retrievePos(tempRider);
                rookie = riderList->retrieveData(tempRiderNode);
                tempMember.setRookie(rookie);
            }
            tempMember.setRookie(rookie);
        }
    } else {
        cout << "Make sure after adding riders to add them to " << userName << endl;
        cin.ignore();
        enterToContinue();
    }
    tempMember.setRiderCount(riderCount);
    memberList->insertData(memberList->getFirstPos(), tempMember);
}

void MemberMenu::deleteMember() {

}

void MemberMenu::modifyMember() {

}

void MemberMenu::enterToContinue() {
    cout << "Press enter to continue" << endl;
    getchar();
}
