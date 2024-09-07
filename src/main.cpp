#include <iostream>

#include "menu.h"

int main() {
    cout << "\033[40m"; // black background
    cout << "\x1b[37m"; // white text

    new Menu();
    return 0;
}
