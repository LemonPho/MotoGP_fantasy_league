#include "rider-menu.h"

RiderMenu::RiderMenu(MemberList *memberList, string &seasonName) {
    this->memberList = memberList;
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
        cout << "2. Modify Rider" << endl;
        cout << "3. Delete Rider" << endl;
        cout << "4. List Riders" << endl;
        cout << "5. Delete ALL Riders" << endl;
        cout << "6. Save Changes" << endl;
        cout << "7. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case ADD_RIDER: {
                saveChanges = addRider();
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
                break;
            }
            case DELETE_ALL_RIDERS: {
                char opt;
                cout << "Are you sure you want to continue? (S/N)" << endl;
                cout << "->";
                cin >> opt;
                if(opt == 's' || opt == 'S'){
                    memberList->riderList->deleteAll();
                    saveChanges = true;
                }
                break;
            }
            case SAVE_CHANGES_RIDERS: {
                saveChangesMade();
                break;
            }
            case EXIT_RIDER: {
                char opt;
                if(saveChanges){
                    cout << "Would you like to save the changes made? (S/N)" << endl;
                    cout << "->";
                    cin >> opt;
                    if(opt == 'S' || opt == 's'){
                        saveChangesMade();
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
    tempRider.setData(name, number, country, team, rookie, testRider);
    tempRider.addPoints(points);

    memberList->riderList->insertOrdered(tempRider);
    return true;
}

bool RiderMenu::modifyRider() {
}

bool RiderMenu::deleteRider() {
}

void RiderMenu::listRiders() {

}

void RiderMenu::saveChangesMade() {
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
        memberList->riderList->writeToDisk(currentDirectory + RIDER_DATA);
    }
}

void RiderMenu::enterToContinue() {
    cout << "Press enter to continue" << endl;
    getchar();
}
