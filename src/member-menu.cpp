#include "member-menu.h"
#include "menu.h"

MemberMenu::MemberMenu(MemberList *memberList, RiderList *riderList, string &seasonName) {
    this->memberList = memberList;
    this->riderList = riderList;
    this->seasonName = seasonName;
    saveChanges = false;
    //updateMemberPoints();
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
                saveChanges = addMember();
                //updateMemberPoints();
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
        cout << "3. Change Rookie" << endl;
        cout << "4. Save Changes" << endl;
        cout << "5. Exit" << endl;
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
                tempNode->setData(&tempMember);
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
                cout << "Input the username of the member's riders you would like to modify" << endl;
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
                cout << "Input rider number" << endl;
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
                cout << "Input new rider number: " << endl;
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
            case CHANGE_ROOKIE: {
                system(CLEAR);
                string userName;
                Member tempMember;
                MemberNode* tempMemberNode = new MemberNode();

                string riderNumber;
                Rider tempRider;
                RiderNode* tempRiderNode = new RiderNode();

                bool endModify = false;
                system(CLEAR);
                cout << "Modify Member Rookie" << endl;

                cout << memberList->toString() << endl;
                cout << "Input the username of the member's riders you would like to modify" << endl;
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
                cout << "Modify Member Rookie" << endl;
                cout << riderList->toString() << endl;
                cout << "Input new rider number: " << endl;
                cout << "-> ";
                getline(cin, riderNumber);
                tempRider.setNumber(riderNumber);
                tempRiderNode = riderList->retrievePos(tempRider);
                if(tempRiderNode == nullptr || !tempRiderNode->getData().getRookie()){
                    endModify = false;
                    while((tempRiderNode == nullptr || !tempRiderNode->getData().getRookie()) && !endModify){
                        cout << "Rider not found or not a rookie, input number again (0 to cancel)" << endl;
                        cout << "-> ";
                        getline(cin, riderNumber);
                        if(riderNumber == "0"){
                            endModify = true;
                        } else {
                            tempRider.setNumber(riderNumber);
                            tempRiderNode = riderList->retrievePos(tempRider);
                        }
                    }
                    if(endModify){
                        return;
                    }
                }

                tempRider = tempRiderNode->getData();
                tempMember.setRookie(tempRider);
                memberList->insertData(tempMemberNode, tempMember);

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
