#include "util.h"

//fills needed spaces to print everything aligned
string fillSpaces(string line, int spaces){
    if(!spaces){
        return line;
    }
    for(int i = 0; i < spaces; i++){
        line += " ";
    }
    return line;
}

void printMenu(string menuOptions[], int optionCount){
    for(int i = 0; i <= optionCount; i++){
        cout << endl;
        cout << "\t" << menuOptions[i];
    }
}

void gotoxy(int x, int y){
    cout << "\033[" << y << ";" << x << "H";
}

void updateMenu(int option, int left, int right){
    gotoxy(left, option);
    cout << "->";
    gotoxy(right, option);
    cout << "<-";
}

void clearSelection(int start, int end, int left, int right){
    for(int i = start; i < end+1; i++){
        gotoxy(left, i);
        cout << "  ";
        gotoxy(right, i);
        cout << "  ";
    }
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void enterToContinue(){
    cout << "Press enter to continue..." << endl;
    getchar();
}

int checkIfSelected(const int selections[], int selectionsLength, int query){
    for(int i = 0; i < selectionsLength; i++){
        if(selections[i] == query){
            return i;
        }
    }

    return -1;
}

int unix_getch(){
	struct termios oldSettings, newSettings;
	int key;

    //current settings
	tcgetattr(STDIN_FILENO, &oldSettings);

    //save settings temporarily
    newSettings = oldSettings;

    //disable buffered io and echoing
    newSettings.c_lflag &= ~(ICANON | ECHO);

    // apply settings 
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    key = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

    return key;
}