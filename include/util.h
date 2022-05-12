#ifndef MOTOGP_FANTASY_LEAGUE_UTIL_H
#define MOTOGP_FANTASY_LEAGUE_UTIL_H

#include <iostream>

using namespace std;

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
#endif //MOTOGP_FANTASY_LEAGUE_UTIL_H
