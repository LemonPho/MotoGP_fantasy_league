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
                memberList->deleteAll();
                memberList = new MemberList();
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


    string temp;
    string tempSeasonName;
    string directory, homeDirectory;
    char tempDirectory[256];
    int success;
    char option;

    cout << "Creating season" << endl;
    cout << "Input the season name (change spaces for -): ";
    getline(cin, temp);
    directory += temp + "/";
    homeDirectory = getenv("HOME");
    sprintf(tempDirectory, "%s/%s", homeDirectory.data(), directory.data());
    directory = tempDirectory;
    /*
    success = mkdir(directory.data(), S_IRWXU);
    if (success != 0) {
        cout << "Couldn't create directory, error: " << success << endl;
        return;
    }*/
    cout << "Would you like to make it the default season? (S/N): ";
    cin >> option;
    if(option == 'S' || option == 's'){
        fstream file(PROGRAM_DATA, ios::out);
        if(!file.is_open()){
            cout << "Error couldn't open " << PROGRAM_DATA << endl;
            enterToContinue();
            return;
        }
        file << directory;
        file.close();
    }
}

void SeasonMenu::changeSeason() {

}

void SeasonMenu::changeDefaultSeason() {

}

void SeasonMenu::enterToContinue() {
    cout << "Press enter to continue" << endl;
    getchar();
}
