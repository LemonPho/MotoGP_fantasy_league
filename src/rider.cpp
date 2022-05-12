#include "rider.h"

Rider::Rider() {
    name = Name();
    number = "NUMBER";
    country = "COUNTRY";
    team = "ROOKIE";
    rookie = false;
    testRider = false;
    chosen = false;
    points = 0;
}

bool Rider::setData(Name &name, string &number, string &country, string &team, bool &rookie, bool &testRider) {
    if(rookie && testRider){
        return false;
    }
    this->name = name;
    this->number = number;
    this->country = country;
    this->team = team;
    this->rookie = rookie;
    this->testRider = testRider;
    return true;
}

void Rider::addPoints(int &points) {
    this->points += points;
}

void Rider::setChosen(bool &chosen) {
    this->chosen = chosen;
}

Name Rider::getName() {
    return name;
}

string Rider::getNumber() {
    return number;
}

string Rider::getCountry() {
    return country;
}

string Rider::getTeam() {
    return team;
}

bool Rider::getRookie() {
    return rookie;
}

bool Rider::getTestRider() {
    return testRider;
}

//toString is used to print the rider to the screen
string Rider::toString() {
    string result;

    result += fillSpaces(number, SPACE_NUMBER - number.length());
    result += "|";
    result += name.toString();
    result += "|";
    result += fillSpaces(country, SPACE_COUNTRY - country.length());
    result += "|";
    result += fillSpaces(team, SPACE_TEAM - team.length());
    result += "|";
    if(rookie){
        result += "(R)|";
    }
    if(testRider){
        result += "(T)|";
    }
    if(chosen){
        result += "*";
    }

    return result;
}

//toStringSmall prints the rider but sumarized for listing
string Rider::toStringSmall() {
    string result;
    string firstName = name.getFirstName();
    string lastName = name.getLastName();

    result += firstName[0];
    result += ". ";
    result += lastName;
    result += " - ";
    result += to_string(points);

    result = fillSpaces(result, SPACE_PRINT_SMALL - result.length());

    return result;
}
