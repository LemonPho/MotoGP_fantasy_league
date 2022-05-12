#include "member.h"

Member::Member() {
    userName = "USER_NAME";
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

string Member::toStringSmall() {
    string result;

    result += userName;
    result += " - ";
    result += to_string(points);

    result = fillSpaces(result, SPACE_USERNAME - result.length());

    for(int i = 0; i < RIDER_COUNT; i++){
        result += riders[i].toStringSmall();
        result += "| ";
    }

    result += rookie.toStringSmall();
    result += "|";

    return result;
}
