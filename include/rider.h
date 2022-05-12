#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_H

#include <iostream>

#include "name.h"
#include "util.h"

using namespace std;

//space used by each category when printing
#define SPACE_NUMBER 2
#define SPACE_COUNTRY 10
#define SPACE_TEAM 25
//space used when printing riders sumarized
#define SPACE_PRINT_SMALL 35

//rider
class Rider {
private:
    //attributes
    Name name;
    string number;
    string country;
    string team;
    bool rookie;
    bool testRider;
    bool chosen;
    int points;
public:
    //functions
    Rider();

    bool setData(Name &name, string &number, string &country, string &team, bool &rookie, bool &testRider);
    void setChosen(bool &chosen);
    void addPoints(int &points);

    Name getName();
    string getNumber();
    string getCountry();
    string getTeam();
    bool getRookie();
    bool getTestRider();

    string toString();
    string toStringSmall();
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_H
