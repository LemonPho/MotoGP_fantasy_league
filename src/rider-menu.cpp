#include "rider-menu.h"
#include "util.h"

RiderMenu::RiderMenu(MemberList* memberList, RiderList *riderList, string &seasonName, ErrorMessage *errorMessage) {
    this->errorMessage = errorMessage;
    this->memberList = memberList;
    this->riderList = riderList;
    this->seasonName = seasonName;
    saveChanges = false;
    menu();
}

void RiderMenu::menu() {
    bool end = false;
    int option;
    do{
        system(CLEAR);
        cout << "Rider Menu" << endl;

        if(errorMessage != nullptr && !errorMessage->isEmpty()){
            cout << endl << errorMessage->getErrorMessage() << endl;
        }

        cout << "1. Race Results Menu" << endl;
        cout << "2. Add Rider" << endl;
        cout << "3. Delete Rider" << endl;
        cout << "4. List Riders" << endl;
        cout << "5. Delete ALL Riders" << endl;
        cout << "6. Save Changes" << endl;
        cout << "7. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case RACE_RESULTS_MENU: {
                new RaceResultsMenu(riderList, memberList, seasonName);
                riderList->modifyFromDisk(seasonName + '-' + RIDER_DATA);
                memberList->modifyFromDisk(seasonName + '-' + MEMBER_DATA);
                break;
            }
            case ADD_RIDER: {
                saveChanges = addRider();
                break;
            }
            case DELETE_RIDER: {
                saveChanges = deleteRider();
                break;
            }
            case LIST_RIDERS: {
                system(CLEAR);
                cout << riderList->toString() << endl;
                clearBuffer();
                enterToContinue();
                break;
            }
            case DELETE_ALL_RIDERS: {
                char opt;
                cout << "Are you sure you want to continue? (S/N)" << endl;
                cout << "->";
                cin >> opt;
                if(opt == 's' || opt == 'S'){
                    riderList->deleteAll();
                    saveChanges = true;
                }
                break;
            }
            case SAVE_CHANGES_RIDERS: {
                riderList->writeToDisk(seasonName + '-' + RIDER_DATA);
                saveChanges = false;
                break;
            }
            case EXIT_RIDER: {
                char opt;
                if(saveChanges){
                    cout << "Would you like to save the changes made? (S/N)" << endl;
                    cout << "->";
                    cin >> opt;
                    if(opt == 'S' || opt == 's'){
                        riderList->writeToDisk(seasonName + '-' + RIDER_DATA);
                        memberList->writeToDisk(seasonName + '-' + MEMBER_DATA);
                        saveChanges = false;
                    }
                }
                end = true;
                break;
            }
            default: {
                cout << "Select a valid option" << endl;
                clearBuffer();
                enterToContinue();
            }
        }
    }while(!end);
}

bool RiderMenu::addRider() {
    string firstName, lastName, number, country, team;
    bool rookie = false, testRider = false;
    int points;
    Rider tempRider;
    RiderManager tempRiderManager;
    char option;

    system(CLEAR);
    cout << "Add Rider" << endl;
    cout << "Input the first name" << endl;
    cout << "->";
    cin.ignore();
    getline(cin, firstName);
    cout << "Input the last name" << endl;
    cout << "->";
    getline(cin, lastName);
    cout << "Input the number" << endl;
    cout << "->";
    getline(cin, number);
    cout << "Input the country" << endl;
    cout << "->";
    getline(cin, country);
    cout << "Input the team" << endl;
    cout << "->";
    getline(cin, team);
    cout << "Input the points" << endl;
    cout << "->";
    cin >> points;

    tempRider.setData(firstName, lastName, number, country, team);
    tempRiderManager.setPoints(points);
    tempRiderManager.setRider(tempRider);

    riderList->insertOrdered(tempRiderManager);
    return true;
}

/*
bool RiderMenu::addRaceResults() {
    system(CLEAR);

    RiderNode* temp(riderList->getFirstPos());
    Rider tempRider;
    RiderManager tempRiderManager;
    int position;
    int points[25] = {25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int riderPoints;
    string line;

    cout << "Add Race Results" << endl;
    while(temp != nullptr){
        riderPoints = 0;
        line = temp->getData().toStringSmallFullName();
        tempRiderManager = temp->getData();
        cout << line << endl;
        cout << "Input final race position" << endl;
        cout << "->";
        cin >> position;
        if(position < 16 && position > 0) {
            riderPoints += tempRiderManager.getPoints();
            riderPoints += points[position-1];
            tempRiderManager.setPoints(riderPoints);
            temp->setData(tempRiderManager);
        }
        temp = temp->getNext();
    }
    memberList->updateMembersRiders(riderList);
    return true;
}

bool RiderMenu::addRaceResultsAutomatic() {
    system(CLEAR);
    string url;
    bool changes = false;

    cout << "Add Race Results Automatic" << endl;
    cout << "Paste the link of the race result from motorsport.com" << endl;
    cout << "->";
    cin >> url;

    RaceResultScraper raceResultScraper = RaceResultScraper(riderList, url, errorMessage);
    if(!raceResultScraper.get()){
        //MUST CONVERT THESE TO AN ERROR MESSAGE INSIDE THE RIDERMENU OBJECT
        cout << "Error retrieving results, be sure the link is correct" << endl;
        clearBuffer();
        enterToContinue();
        return changes;
    }

    if(!raceResultScraper.saveHTML()){
        cout << "Error creating the temporary html file" << endl;
        clearBuffer();
        enterToContinue();
        return changes;
    }

    if(!raceResultScraper.parseHTML()){
        cout << "Error reading the html file" << endl;
        clearBuffer();
        enterToContinue();
        return changes;
    }

    cout << "Retrieved race result" << endl;


    system(CLEAR);
    int confirmChanges;
    cout << tempRiderList->toString();
    cout << "1. Accept race result" << endl;
    cout << "2. Cancel race result" << endl;
    cout << "Option: ";
    cin >> confirmChanges;
    if(confirmChanges == 1){
        changes = true;
        for(int i = 0; i < raceResultScraper.getRidersIndex(); i++){
            tempNumber = raceResultScraper.getRiderManager(i).getRider().getNumber();
            tempPoints = raceResultScraper.getRiderManager(i).getPoints();

            tempRider.setNumber(tempNumber);
            tempRiderManager.setRider(tempRider);
            tempRiderNode = riderList->retrievePos(tempRiderManager);

            if(tempRiderNode == nullptr){
                if(errorMessage != nullptr){
                    errorMessage->addErrorMessage("Couldn't find data for rider #" + tempRider.getNumber() + "\n");
                } else {
                    cout << "Couldn't find data for rider #" << tempRider.getNumber() << endl;
                }
                return false;
            } else {
                tempPoints += tempRiderNode->getData().getPoints();
                tempRiderManager = tempRiderNode->getData();
                tempRiderManager.setPoints(tempPoints);
                tempRiderNode->setData(tempRiderManager);
            }
        }
    }

    delete tempRiderList;

    if(!raceResultScraper.deleteHTML()){
        cout << "Error deleting the temporary html file" << endl;
        clearBuffer();
        enterToContinue();
        return changes;
    }

    memberList->updateMembersRiders(riderList);
    memberList->updateMembersPoints();

    return changes;
}

bool RiderMenu::addSprintRaceResults() {
    system(CLEAR);

    RiderNode* temp(riderList->getFirstPos());
    Rider tempRider;
    RiderManager tempRiderManager;
    int position;
    int points[25] = {12, 9, 7, 6, 5, 4, 3, 2, 1};
    int riderPoints;
    string line;

    cout << "Add Sprint Race Results" << endl;
    while(temp != nullptr){
        riderPoints = 0;
        line = temp->getData().toStringSmallFullName();
        tempRiderManager = temp->getData();
        cout << line << endl;
        cout << "Input final race position" << endl;
        cout << "->";
        cin >> position;
        if(position < 10 && position > 0) {
            riderPoints += tempRiderManager.getPoints();
            riderPoints += points[position-1];
            tempRiderManager.setPoints(riderPoints);
            temp->setData(tempRiderManager);
        }
        temp = temp->getNext();
    }
    memberList->updateMembersRiders(riderList);
    return true;
}
 */

bool RiderMenu::deleteRider() {
    system(CLEAR);

    string riderNumber;
    Rider tempRider;
    RiderManager tempRiderManager;
    bool found = false;
    RiderNode *tempNode(riderList->getFirstPos());

    cout << "Delete Rider" << endl;
    cout << riderList->toString() << endl;
    cout << "Input rider number to delete: ";
    cin.ignore();getline(cin, riderNumber);
    tempRider.setNumber(riderNumber);
    tempRiderManager.setRider(tempRider);

    while(tempNode != nullptr){
        if(tempNode->getData() == tempRiderManager){
            riderList->deleteData(tempNode);
            found = true;
        }
        tempNode = tempNode->getNext();
    }

    if(found){
        cout << "Rider deleted successfully" << endl;
        enterToContinue();
        return true;
    }

    if(errorMessage != nullptr){
        errorMessage->addErrorMessage("Rider not found with number: " + riderNumber);
        return false;
    }

    cout << "Rider not found with number: " << riderNumber << endl;
    enterToContinue();
    return false;

}
