#include "menu.h"

Menu::Menu() {
    if(!currentDirectory.empty()){
        memberList = memberList->readFromDisk(currentDirectory + FILENAME);
    } else {
        memberList = new MemberList();
        currentDirectory = ".";
        firstStart();
    }
}

void Menu::firstStart() {
    int success;
    string homeDirectory, temp;
    char tempDirectory[256];

    cout << "Wellcome to the MotoGP Fantasy League Manager" << endl;
    cout << "Input a name for the current season: ";
    getline(cin, temp);
    currentDirectory += temp + "/";

    homeDirectory = getenv("HOME");
    sprintf(tempDirectory, "%s/%s", homeDirectory.data(), currentDirectory.data());

    currentDirectory = tempDirectory;
    success = mkdir(currentDirectory.data(), S_IRWXU);
    if(success != 0){
        cout << "Couldn't create directory, error: " << success << endl;
    }
}

void Menu::menu() {

}

void Menu::enterToContinue() {

}
