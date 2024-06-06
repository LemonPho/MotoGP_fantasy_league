#ifndef MOTOGP_FANTASY_LEAGUE_RIDER_H
#define MOTOGP_FANTASY_LEAGUE_RIDER_H

#include <iostream>

#include "util.h"

using namespace std;

//space used by each category when printing
#define SPACE_POSITION 2
#define SPACE_NUMBER 2
#define SPACE_COUNTRY 20
#define SPACE_TEAM 40
#define SPACE_POINTS 4
#define SPACE_NAME 25
//space used when printing riders sumarized
#define SPACE_PRINT_SMALL 25

//rider
class Rider {
private:
    //attributes
    string firstName, lastName;
    string number;
    string country;
    string team;
public:
    //functions
    Rider();

    bool setData(string &firstName, string &lastName, string &number, string &country, string &team);
    void setNumber(string &number);
    void setFirstName(string &firstName);

    string getFirstName();
    string getLastName();
    string getNumber();
    string getCountry();
    string getTeam();

    Rider& operator = (const Rider &rider);
    bool operator == (const Rider &rider);
    bool operator != (const Rider &rider);
    bool operator < (const Rider &rider);
    bool operator <= (const Rider &rider);
    bool operator > (const Rider &rider);
    bool operator >= (const Rider &rider);
};

#endif //MOTOGP_FANTASY_LEAGUE_RIDER_H
