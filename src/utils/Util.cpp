#include "utils/util.h"

namespace util {

//fills needed spaces to print everything aligned
    std::string FillSpaces(std::string line, int spaces){
        if(!spaces){
            return line;
        }
        for(int i = 0; i < spaces; i++){
            line += " ";
        }
        return line;
    }

    void gotoxy(size_t x, size_t y){
        std::cout << "\033[" << y << ";" << x << "H";
    }

    void UpdateArrowPosition(size_t line, size_t left, size_t right){
        gotoxy(left, line);
        std::cout << "->";
        gotoxy(right, line);
        std::cout << "<-";
    }

    void ClearText(size_t start, size_t end, size_t left, size_t right){
        if (start == end) {
            gotoxy(left, start);
            std::cout << "  ";
            gotoxy(right, start);
            std::cout << "  ";
        }

        for(size_t i = start; i < end+1; i++){
            gotoxy(left, i);
            std::cout << "  ";
            gotoxy(right, i);
            std::cout << "  ";
        }
    }

    void ClearBuffer(){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    void EnterToContinue(){
        std::cout << "Press enter to continue..." << std::endl;
        getchar();
    }

    int CheckIfSelected(const int selections[], int selectionsLength, int query){
        for(int i = 0; i < selectionsLength; i++){
            if(selections[i] == query){
                return i;
            }
        }

        return -1;
    }

#ifdef _WIN32
int CustomGetch() {
    return _getch();
}
void GetWindowDimensions(int& columns, int& rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        // The number of columns (width)
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        // The number of rows (height)
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else {
        // If the function fails, return some default value
        columns = 80;
        rows = 25;
    }
}
#else
int CustomGetch(){
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

void UpdateProgram(){
    char input;
    std::cout << "Are you sure you want to update the program? It will be close to update. (Y/N): ";
    std::cin >> input;

    if(input == 'Y' || input == 'y'){
        std::cout << "Be sure to copy the update_macos.sh file into the home directory" << std::endl;
        std::cout << "This is done by copying the file, clicking on Go in the top bar, then selecting home" << std::endl;
        std::cout << "Once in the home directory you may paste the file there" << std::endl;
        std::cout << "When the file is pasted in the home directory, ";
        ClearBuffer();
        EnterToContinue();
        system("rm -rf MotoGP_fantasy_league");
        system("chmod +x update_macos.sh");
        system("./update_macos.sh");
        EnterToContinue();
    }
}

void GetWindowDimensions(int& columns, int& rows) {
    struct winsize w;

    // Use ioctl to get terminal size
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        // Set the number of columns and rows
        columns = w.ws_col;
        rows = w.ws_row;
    }
    else {
        // If the function fails, return some default value
        columns = 80;
        rows = 25;
    }
}
#endif

}
