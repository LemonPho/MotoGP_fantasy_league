#include "rider.h"

Rider::Rider() {
    firstName = "";
    lastName = "";
    number = "";
    country = "";
    team = "";
}

bool Rider::setData(string &firstName, string &lastName, string &number, string &country, string &team) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->number = number;
    this->country = country;
    this->team = team;
    return true;
}

void Rider::setNumber(string &number) {
    if(stoi(number) >= 1 && stoi(number) <= 99){
        this->number = number;
    }
}

void Rider::setFirstName(std::string &firstName) {
    this->firstName = firstName;
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

Rider &Rider::operator=(const Rider &rider) {
    firstName = rider.firstName;
    lastName = rider.lastName;
    number = rider.number;
    country = rider.country;
    team = rider.team;

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
