#include "rider-menu.h"
#include "util.h"

RiderMenu::RiderMenu(MemberList* memberList, RiderList *riderList, string &seasonName) {
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
        cout << "1. Add Rider" << endl;
        cout << "2. Import Race Results from motosport.com" << endl;
        cout << "3. Add Race Results" << endl;
        cout << "4. Add Sprint Race Results" << endl;
        cout << "5. Delete Rider" << endl;
        cout << "6. List Riders" << endl;
        cout << "7. Delete ALL Riders" << endl;
        cout << "8. Save Changes" << endl;
        cout << "9. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case ADD_RIDER: {
                saveChanges = addRider();
                break;
            }

            case AUTOMATIC_ADD_RACE_RESULTS: {
                saveChanges = addRaceResultsAutomatic();
                break;
            }

            case ADD_RACE_RESULTS: {
                saveChanges = addRaceResults();
                break;
            }
            case ADD_SPRINT_RACE_RESULTS: {
                saveChanges = addSprintRaceResults();
                break;
            }
            case DELETE_RIDER: {
                saveChanges = deleteRider();
                break;
            }
            case LIST_RIDERS: {
                system(CLEAR);
                cout << riderList->toString() << endl;
                cin.ignore();
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
                        saveChanges = false;
                    }
                }
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

bool RiderMenu::addRider() {
    string firstName, lastName, number, country, team;
    bool rookie = false, testRider = false;
    int points;
    Rider tempRider;
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

    tempRider.setData(firstName, lastName, number, country, team, points);

    riderList->insertOrdered(tempRider);
    return true;
}

bool RiderMenu::addRaceResults() {
    system(CLEAR);

    RiderNode* temp(riderList->getFirstPos());
    Rider tempRider;
    int position;
    int points[25] = {25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int riderPoints;
    string line;

    cout << "Add Race Results" << endl;
    while(temp != nullptr){
        riderPoints = 0;
        line = temp->getData().toStringSmallFullName();
        tempRider = temp->getData();
        cout << line << endl;
        cout << "Input final race position" << endl;
        cout << "->";
        cin >> position;
        if(position < 16 && position > 0) {
            riderPoints += tempRider.getPoints();
            riderPoints += points[position-1];
            tempRider.setPoints(riderPoints);
            temp->setData(tempRider);
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

    RaceResultScraper raceResultScraper = RaceResultScraper(riderList, url);
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

    cout << "Retrieved race results" << endl;
    //be sure to free the rider list
    bool error = false;
    RiderList* tempRiderList = new RiderList();
    RiderNode* tempRiderNode = new RiderNode();
    Rider tempRider = Rider();
    string tempNumber;
    int tempPoints, tempPosition;
    for(int i = 0; i < raceResultScraper.getRidersIndex(); i++){
        tempNumber = raceResultScraper.getRider(i).getNumber();
        tempPoints = raceResultScraper.getRider(i).getPoints();
        tempPosition = raceResultScraper.getRider(i).getPosition();

        tempRider.setNumber(tempNumber);
        tempRiderNode = riderList->retrievePos(tempRider);

        if(tempRiderNode == nullptr){
            cout << "Couldn't find data for rider #" << tempRider.getNumber() << endl;
            error = true;
        } else {
            tempRider = tempRiderNode->getData();
            tempRider.setPoints(tempPoints);
            tempRider.setPosition(tempPosition);
            tempRiderList->insertOrdered(tempRider);
        }
    }

    if(error){
        cout << "Results wont be saved" << endl;
        clearBuffer();
        enterToContinue();

        return changes;
    }

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
            tempNumber = raceResultScraper.getRider(i).getNumber();
            tempPoints = raceResultScraper.getRider(i).getPoints();

            tempRider.setNumber(tempNumber);
            tempRiderNode = riderList->retrievePos(tempRider);

            if(tempRiderNode == nullptr){
                cout << "Couldn't find data for rider #" << tempRider.getNumber() << endl;
                error = true;
            } else {
                tempPoints += tempRiderNode->getData().getPoints();
                tempRider = tempRiderNode->getData();
                tempRider.setPoints(tempPoints);
                tempRiderNode->setData(tempRider);
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
    int position;
    int points[25] = {12, 9, 7, 6, 5, 4, 3, 2, 1};
    int riderPoints;
    string line;

    cout << "Add Sprint Race Results" << endl;
    while(temp != nullptr){
        riderPoints = 0;
        line = temp->getData().toStringSmallFullName();
        tempRider = temp->getData();
        cout << line << endl;
        cout << "Input final race position" << endl;
        cout << "->";
        cin >> position;
        if(position < 10 && position > 0) {
            riderPoints += tempRider.getPoints();
            riderPoints += points[position-1];
            tempRider.setPoints(riderPoints);
            temp->setData(tempRider);
        }
        temp = temp->getNext();
    }
    memberList->updateMembersRiders(riderList);
    return true;
}

bool RiderMenu::deleteRider() {
    system(CLEAR);

    string riderNumber;
    Rider tempRider;
    bool found = false;
    RiderNode *tempNode(riderList->getFirstPos());

    cout << "Delete Rider" << endl;
    cout << riderList->toString() << endl;
    cout << "Input rider number to delete: ";
    cin.ignore();getline(cin, riderNumber);
    tempRider.setNumber(riderNumber);

    while(tempNode != nullptr){
        if(tempNode->getData() == tempRider){
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
    cout << "Rider not deleted successfully" << endl;
    enterToContinue();
    return false;

}
