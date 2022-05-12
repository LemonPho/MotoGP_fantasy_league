#include "member.h"

Member::Member() {
    userName = "";
    for(int i = 0; i < RIDER_COUNT; i++){
        riders[i] = Rider();
    }
    rookie = Rider();
    riderCount = 0;
    points = 0;
}

Member::Member(const Member &member) {
    this->userName = member.userName;
    for(int i = 0; i < member.riderCount; i++){
        this->riders[i] = member.riders[i];
    }
    this->rookie = member.rookie;
    this->riderCount = member.riderCount;
    this->points = member.points;
}

bool Member::setUserName(string &userName) {
    if(userName.length() > 35){
        return false;
    }
    this->userName = userName;
    return true;
}

void Member::setRider(Rider &rider) {
    riders[riderCount++] = rider;
}

void Member::setRookie(Rider &rookie) {
    this->rookie = rookie;
}

void Member::addPoints(int &points) {
    this->points += points;
}

string Member::getUserName() {
    return userName;
}

Rider *Member::getRiders() {
    return riders;
}

Rider Member::getRookie() {
    return rookie;
}

int Member::getRiderCount() {
    return riderCount;
}

int Member::getPoints() {
    return points;
}

string Member::getRidersDisk() {
    string result = "";

    for(int i = 0; i < riderCount; i++){
        result += riders[i].toStringDisk();
    }

    return result;
}

string Member::toStringSmall() {
    string result;

    result += userName;
    result += " - ";
    result += to_string(points);

    result = fillSpaces(result, SPACE_USERNAME - result.length());

    for(int i = 0; i < riderCount; i++){
        result += riders[i].toStringSmall();
        result += "| ";
    }

    if(rookie.getNumber() == "NUMBER") {
        result += rookie.toStringSmall();
        result += "|";
    }

    return result;
}
