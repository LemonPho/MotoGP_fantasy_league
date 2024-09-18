#include "util.h"

//fills needed spaces to print everything aligned
std::string util::FillSpaces(std::string line, int spaces){
    if(!spaces){
        return line;
    }
    for(int i = 0; i < spaces; i++){
        line += " ";
    }
    return line;
}

void util::PrintMenu(std::string menuOptions[], int optionCount){
    for(int i = 0; i <= optionCount; i++){
        std::cout << std::endl;
        std::cout << "\t" << menuOptions[i];
    }
}

void util::gotoxy(int x, int y){
    std::cout << "\033[" << y << ";" << x << "H";
}

void util::UpdateMenu(int option, int left, int right){
    util::gotoxy(left, option);
    std::cout << "->";
    util::gotoxy(right, option);
    std::cout << "<-";
}

void util::ClearSelection(int start, int end, int left, int right){
    for(int i = start; i < end+1; i++){
        util::gotoxy(left, i);
        std::cout << "  ";
        util::gotoxy(right, i);
        std::cout << "  ";
    }
}

void util::ClearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void util::EnterToContinue(){
    std::cout << "Press enter to continue..." << std::endl;
    getchar();
}

int util::CheckIfSelected(const int selections[], int selectionsLength, int query){
    for(int i = 0; i < selectionsLength; i++){
        if(selections[i] == query){
            return i;
        }
    }

    return -1;
}

#ifdef _WIN32
int util::CustomGetch() {
    return _getch();
}
#else
int util::CustomGetch(){
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

void util::UpdateProgram(){
    char input;
    std::cout << "Are you sure you want to update the program? It will be close to update. (Y/N): ";
    std::cin >> input;

    if(input == 'Y' || input == 'y'){
        std::cout << "Be sure to copy the update_macos.sh file into the home directory" << std::endl;
        std::cout << "This is done by copying the file, clicking on Go in the top bar, then selecting home" << std::endl;
        std::cout << "Once in the home directory you may paste the file there" << std::endl;
        std::cout << "When the file is pasted in the home directory, ";
        util::ClearBuffer();
        util::EnterToContinue();
        system("rm -rf MotoGP_fantasy_league");
        system("chmod +x update_macos.sh");
        system("./update_macos.sh");
        util::EnterToContinue();
    }
}
#endif