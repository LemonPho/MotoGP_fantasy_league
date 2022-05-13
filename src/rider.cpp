#include "rider.h"

Rider::Rider() {
    firstName = "";
    lastName = "";
    number = "";
    country = "";
    team = "";
    rookie = false;
    testRider = false;
    chosen = false;
    points = 0;
}

bool Rider::setData(string &firstName, string &lastName, string &number, string &country, string &team, int &points, bool &rookie, bool &testRider) {
    if(rookie && testRider){
        return false;
    }
    this->firstName = firstName;
    this->lastName = lastName;
    this->number = number;
    this->country = country;
    this->team = team;
    this->points = points;
    this->rookie = rookie;
    this->testRider = testRider;
    return true;
}

void Rider::setNumber(string &number) {
    this->number = number;
}

void Rider::setPoints(int &points) {
    this->points = points;
}

void Rider::setChosen(bool &chosen) {
    this->chosen = chosen;
}

string Rider::getFirstName() {
    return firstName;
}

string Rider::getLastName(){
    return lastName;
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

bool Rider::getChosen() {
    return chosen;
}

int Rider::getPoints() {
    return points;
}

//toString is used to print the rider to the screen
string Rider::toString() {
    string result;
    string name = firstName + " " + lastName;

    result += fillSpaces(number, SPACE_NUMBER - number.length());
    result += "|";
    result += fillSpaces(name, SPACE_NAME - name.length());
    result += "|";
    result += fillSpaces(to_string(points), SPACE_POINTS - to_string(points).length());
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

    result += firstName[0];
    result += ". ";
    result += lastName;
    result += " - ";
    result += to_string(points);

    result = fillSpaces(result, SPACE_PRINT_SMALL - result.length());

    return result;
}

string Rider::toStringDisk() {
    string result;

    result += number;
    result += "|";
    result += firstName;
    result += " ";
    result += lastName;
    result += "|";
    result += country;
    result += "|";
    result += team;
    result += "|";
    result += to_string(points);
    result += "|";
    if(rookie){
        result += "(R)|";
    } else {
        result += " |";
    }
    if(testRider){
        result += "(T)|";
    } else {
        result += " |";
    }
    if(chosen){
        result += "*";
    } else {
        result += " ";
    }

    return result;
}

Rider &Rider::operator=(const Rider &rider) {
    firstName = rider.firstName;
    lastName = rider.lastName;
    number = rider.number;
    country = rider.country;
    team = rider.team;
    rookie = rider.rookie;
    testRider = rider.testRider;
    chosen = rider.chosen;
    points = rider.points;

    return *this;
}

bool Rider::operator==(const Rider &rider) {
    return stoi(number) == stoi(rider.number);
}

bool Rider::operator!=(const Rider &rider) {
    return stoi(number) != stoi(rider.number);
}

bool Rider::operator<(const Rider &rider) {
    return stoi(number) < stoi(rider.number);
}

bool Rider::operator<=(const Rider &rider) {
    return stoi(number) <= stoi(rider.number);
}

bool Rider::operator>(const Rider &rider) {
    return stoi(number) > stoi(rider.number);
}

bool Rider::operator>=(const Rider &rider) {
    return stoi(number) >= stoi(rider.number);
}
