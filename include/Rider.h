#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_RIDER_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_RIDER_H

#include <iostream>

class Rider {
public:
    static const int SPACE_POSITION = 2;
    static const int SPACE_NUMBER = 2;
    static const int SPACE_COUNTRY = 20;
    static const int SPACE_TEAM = 40;
    static const int SPACE_POINTS = 4;
    static const int SPACE_NAME = 25;
    static const int SPACE_PRINT_SMALL = 25;
private:
    std::string m_FirstName, m_LastName;
    std::string m_Number;
    std::string m_Country;
    std::string m_Team;
public:
    Rider();

    bool SetData(const std::string &firstName, const std::string &lastName, const std::string &number, const std::string &country, const std::string &team);
    bool SetNumber(const std::string &number);
    void SetFirstName(const std::string &firstName);
    void SetLastName(const std::string &lastName);

    std::string GetFirstName();
    std::string GetLastName();
    std::string GetNumber();
    std::string GetCountry();
    std::string GetTeam();

    Rider& operator = (const Rider &rider);
    bool operator == (const Rider &rider);
    bool operator != (const Rider &rider);
    bool operator < (const Rider &rider);
    bool operator <= (const Rider &rider);
    bool operator > (const Rider &rider);
    bool operator >= (const Rider &rider);
};


#endif //MOTOGP_FANTASY_LEAGUE_MODERN_RIDER_H
