#include "util.h"

namespace util {
    const std::string PROGRAM_DATA = "program-data.txt";
    const std::string MEMBER_DATA = "-member-data.txt";
    const std::string RIDER_DATA = "-rider-data.txt";
    const std::string RACE_DATA = "-race-data.txt";
    std::filesystem::path APP_DIRECTORY;
    std::filesystem::path APP_DIRECTORY_DATA;
    std::filesystem::path APP_DIRECTORY_LOG;
    std::filesystem::path DOWNLOADS_DIRECTORY;

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

    void PrintMenu(std::vector<std::string> menuOptions){
        for(const auto& option : menuOptions){
            std::cout << std::endl;
            std::cout << "\t" << option;
        }
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
#endif

}
