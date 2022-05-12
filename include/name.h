#ifndef MOTOGP_FANTASY_LEAGUE_NAME_H
#define MOTOGP_FANTASY_LEAGUE_NAME_H

#include <iostream>

#include "util.h"

using namespace std;

#define SPACE_NAME 30

class Name {
private:
    string firstName;
    string lastName;
public:
    Name();

    void setData(string &fn, string &ln);
    string getFirstName();
    string getLastName();
    string getName();

    string toString();
};

#endif //MOTOGP_FANTASY_LEAGUE_NAME_H
