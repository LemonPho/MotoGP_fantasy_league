#include "menu.h"

Menu::Menu() {
    if(!currentDirectory.empty()){
        memberList = memberList->readFromDisk(currentDirectory + FILENAME);
    } else {
        memberList = new MemberList();
        firstStart();
    }
}

void Menu::firstStart() {
    string homeDirectory;
    char tempDirectory[256];

    cout << "Wellcome to the MotoGP Fantasy League Manager" << endl;
    cout << "Input a name for the current season: ";
    getline(cin, currentDirectory);
    currentDirectory += "/";

    homeDirectory = getenv("HOME");
    sprintf(tempDirectory, "%s/Documents/MotoGP-Fantasy-League/%s", homeDirectory.data(), currentDirectory.data());

    currentDirectory = tempDirectory;
}

void Menu::menu() {

}

void Menu::enterToContinue() {

}
