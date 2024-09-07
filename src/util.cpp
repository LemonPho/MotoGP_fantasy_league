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

#ifdef _WIN32
int custom_getch(){
    return _getch();
}
#else
int custom_getch(){
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

void update_program(){
    char input;
    int result;
    cout << "Are you sure you want to update the program? (Y/N): ";
    cin >> input;

    if(input == 'Y' || input == 'y'){
        cout << "Be sure to copy the update_macos.sh file into the home directory" << endl;
        cout << "This is done by copying the file, clicking on Go in the top bar, then selecting home." << endl;
        cout << "Once in the home directory you may paste the file there" << endl;
        cout << "When the file is pasted in the home directory, ";
        clearBuffer();
        enterToContinue();
        result = system("chmod +x ~/Library/'Application Support'/'MotoGP Fantasy League'/update_macos.sh");
        if(result != 0){
            cout << "There was an error enabling the script" << endl;
            enterToContinue();
            return;
        }

        result = system("~/Library/'Application Support'/'MotoGP Fantasy League'/update_macos.sh");
        if(result != 0){
            cout << "There was an error running the update script" << endl;
            enterToContinue();
            return;
        }

        result = system("mv MotoGP_fantasy_league/update_macos.sh ~/Library/'Application Support'/'MotoGP Fantasy League'");
        if(result != 0){
            cout << "Error saving new update script" << endl;
            enterToContinue();
            return;
        }

        system("rm -rf MotoGP_fantasy_league");
        enterToContinue();
    }
}
#endif

bool testDirectory(string directory){
    int result;
    string command = "test -d " + directory;

    result = system(command.c_str());

    if(result == 0){
        return true;
    } else {
        return false;
    }
}

bool testFile(string file){
    int result;
    string command = "test -f " + file;

    result = system(command.c_str());

    if(result == 0){
        return true;
    } else {
        return false;
    }
}

bool makeDirectory(string directory){
    int result;
    string command = "mkdir -p " + directory;

    result = system(command.c_str());

    if(result == 0){
        return true;
    } else {
        return false;
    }
}

bool makeFile(string file){
    int result;
    string command = "touch " + file;

    result = system(command.c_str());

    if(result == 0){
        return true;
    } else {
        return false;
    }
}


