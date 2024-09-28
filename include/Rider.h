#ifndef MOTOGP_FANTASY_LEAGUE_MODERN_RIDER_H
#define MOTOGP_FANTASY_LEAGUE_MODERN_RIDER_H

#include <iostream>
#include <memory>
#include <string>

#include "Logger.h"

class Rider {
public:
    enum spacing{
        SPACE_POSITION = 2,
        SPACE_NUMBER = 2,
        SPACE_COUNTRY = 20,
        SPACE_TEAM = 40,
        SPACE_POINTS = 4,
        SPACE_NAME = 25,
        SPACE_PRINT_SMALL = 15,
    };

private:
    std::string m_FirstName, m_LastName;
    std::string m_Number;
    std::string m_Country;
    std::string m_Team;
    std::shared_ptr<Logger> m_Logger;
public:
    Rider();
    Rider(std::shared_ptr<Logger> logger);

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
