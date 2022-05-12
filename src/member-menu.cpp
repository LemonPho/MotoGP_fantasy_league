#include "member-menu.h"
#include "menu.h"

MemberMenu::MemberMenu(MemberList *memberList, string &seasonName) {
    this->memberList = new MemberList();
    this->seasonName = seasonName;
    saveChanges = false;
    menu();
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
                saveChanges = true;
                break;
            }
            case LIST_MEMBERS: {
                cout << memberList->toString() << endl;
                enterToContinue();
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
                saveChangesMade();
                break;
            }
            case EXIT_MEMBER: {
                if(saveChanges) {
                    char opt;
                    cout << "Would you like to save the unsaved changes? (S/N)" << endl;
                    cout << "->";
                    cin >> opt;
                    if(opt == 's' || opt == 'S'){
                        saveChangesMade();
                    }
                }
                end = true;
                break;
            }
        }
    }while(!end);
}

void MemberMenu::addMember() {
    Member tempMember;
    string userName;
    string riderList;
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

    riderList = memberList->riderList->toString();
    cout << riderList << endl;
    if(riderList != "No riders in list"){
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
            tempRiderNode = memberList->riderList->retrievePos(tempRider);
            tempRider = memberList->riderList->retrieveData(tempRiderNode);
            tempMember.setRider(tempRider);
        }
        cout << "Would you like to add a rookie? (S/N)" << endl;
        cout << "->";
        cin >> option;
        if(option == 's' || option == 'S'){
            cout << "Input the desired rider number" << endl;
            cout << "->";
            cin >> tempRiderNumber;
            tempRider.setNumber(tempRiderNumber);
            tempRiderNode = memberList->riderList->retrievePos(tempRider);
            rookie = memberList->riderList->retrieveData(tempRiderNode);
            while(!rookie.getRookie()){
                cout << "Please input a valid rookie (R)" << endl;
                cout << "->";
                cin >> tempRiderNumber;
                tempRider.setNumber(tempRiderNumber);
                tempRiderNode = memberList->riderList->retrievePos(tempRider);
                rookie = memberList->riderList->retrieveData(tempRiderNode);
                tempMember.setRookie(rookie);
            }
        }
    } else {
        cout << "Make sure after adding riders to add them to " << userName << endl;
        cin.ignore();
        enterToContinue();
    }
    memberList->insertData(memberList->getFirstPos(), tempMember);
}

void MemberMenu::deleteMember() {

}

void MemberMenu::modifyMember() {

}

void MemberMenu::saveChangesMade() {
    char option;

    cout << "Would you like to save changes made? (S/N): ";
    cin >> option;
    if(option == 's' || option == 'S'){
        string homeDirectory, temp, currentDirectory;
        char tempDirectory[256];
        currentDirectory += temp + "/";
        homeDirectory = getenv("HOME");
        sprintf(tempDirectory, "%s/%s", homeDirectory.data(), currentDirectory.data());
        currentDirectory = tempDirectory;
        memberList->writeToDisk(currentDirectory + MEMBER_DATA);
    }

}

void MemberMenu::enterToContinue() {
    cout << "Press enter to continue" << endl;
    getchar();
}
