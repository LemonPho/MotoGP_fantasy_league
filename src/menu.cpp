#include "menu.h"

Menu::Menu() {
    system(CLEAR);
    ifstream file(PROGRAM_DATA);

    if(file.is_open()){
        startProgram();
        menu();
    } else {
        memberList = new MemberList();
        firstStart();
        menu();
    }
}

void Menu::firstStart() {
    int success;
    string homeDirectory, temp;
    char tempDirectory[256];
    ofstream file(PROGRAM_DATA, ios::out);

    cout << "Wellcome to the MotoGP Fantasy League Manager" << endl;
    cout << "Input a name for the current season (replace spaces with: - ): ";
    getline(cin, temp);
    seasonName = temp;

    currentDirectory += temp + "/";
    homeDirectory = getenv("HOME");
    sprintf(tempDirectory, "%s/%s", homeDirectory.data(), currentDirectory.data());
    currentDirectory = tempDirectory;
    file << currentDirectory;
    file.close();
    /*success = mkdir(currentDirectory.data(), S_IRWXU);
    if (success != 0) {
        cout << "Couldn't create directory, error: " << success << endl;
    }*/

}

void Menu::startProgram() {
    ifstream file(PROGRAM_DATA);
    bool end = false;
    int i = 0, j = 0;

    if(!file.is_open()){
        cout << "Error when opening " << PROGRAM_DATA << endl;
        throw exception();
    }
    getline(file, currentDirectory);
    if(currentDirectory.empty()){
        memberList = new MemberList();
        return;
    }
    while(!end){
        if(currentDirectory[i] == '/'){
            j++;
        }
        if(j == 3){
            int k = 0;
            i++;
            while(currentDirectory[i] != '/'){
                seasonName[k] = currentDirectory[i];
                i++;
                k++;
            }
            end = true;
        }
        i++;
    }
    currentDirectory += "/";
    memberList = memberList->readFromDisk(currentDirectory + MEMBER_DATA);
}

void Menu::menu() {
    bool end = false;
    int option;
    do{
        system(CLEAR);
        cout << "MotoGP Fantasy League Manager. Current season: " << seasonName <<  endl;
        cout << "1. Seasons Manager" << endl;
        cout << "2. Members Manager" << endl;
        cout << "3. Riders Manager" << endl;
        cout << "4. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
            case SEASONS_MANAGER: {
                new SeasonMenu(memberList, seasonName);
                break;
            }
            case MEMBERS_MANAGER: {
                new MemberMenu(memberList, seasonName);
                break;
            }
            case RIDERS_MANAGER: {
                new RiderMenu(memberList, seasonName);
                break;
            }
            case EXIT_MENU: {
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

void Menu::enterToContinue() {
    cout << "Press enter to continue..." << endl;
    getchar();
}
