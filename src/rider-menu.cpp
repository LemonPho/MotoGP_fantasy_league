#include "rider-menu.h"

RiderMenu::RiderMenu(RiderList *riderList, string &seasonName) {
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
        cout << "2. Add Race Results" << endl;
        cout << "3. Modify Rider" << endl;
        cout << "4. Delete Rider" << endl;
        cout << "5. List Riders" << endl;
        cout << "6. Delete ALL Riders" << endl;
        cout << "7. Save Changes" << endl;
        cout << "8. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case ADD_RIDER: {
                saveChanges = addRider();
                break;
            }
            case ADD_RACE_RESULTS: {
                saveChanges = addRaceResults();
                break;
            }
            case MODIFY_RIDER: {
                saveChanges = modifyRider();
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
    Name name;
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
    cout << "Is he a rookie? (S/N)" << endl;
    cout << "->";
    cin >> option;
    if(option == 's' || option == 'S'){
        rookie = true;
    }
    cout << "Is he a test rider? (S/N)" << endl;
    cout << "->";
    cin >> option;
    if(option == 's' || option == 'S'){
        testRider = true;
    }
    cout << "Input the points" << endl;
    cout << "->";
    cin >> points;

    name.setData(firstName, lastName);
    tempRider.setData(name, number, country, team, points, rookie, testRider);

    riderList->insertOrdered(tempRider);
    return true;
}

bool RiderMenu::addRaceResults() {
    RiderNode* temp(riderList->getFirstPos());
    int points;
    string line;

    while(temp != nullptr){
        system(CLEAR);
        line = temp->getData().toStringSmall();
        cout << line << endl;
        cout << "Input points obtained from race" << endl;
        cout << "->";
        cin >> points;
        points += temp->getData().getPoints();
        temp->getData().setPoints(points);
        temp = temp->getNext();
    }
    return true;
}

bool RiderMenu::modifyRider() {
}

bool RiderMenu::deleteRider() {
}

void RiderMenu::listRiders() {

}

void RiderMenu::enterToContinue() {
    cout << "Press enter to continue" << endl;
    getchar();
}
