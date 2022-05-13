#include "member.h"

Member::Member() {
    userName = "";
    riderList = new RiderList();
    rookie = Rider();
    riderCount = 0;
    points = 0;
}

Member::Member(const Member &member) {
    this->userName = member.userName;
    this->riderList = member.riderList;
    this->rookie = member.rookie;
    this->riderCount = member.riderCount;
    this->points = member.points;
}

bool Member::setUserName(string &userName) {
    if(userName.length() > MAX_USERNAME){
        return false;
    }
    this->userName = userName;
    return true;
}

void Member::insertRider(Rider &rider) {
    RiderNode* temp(riderList->getFirstPos());
    while(temp != nullptr){
        temp = temp->getNext();
    }
    riderList->insertData(temp, rider);
}

void Member::setRiderList(RiderList *riderList) {
    this->riderList = riderList;
}

void Member::setRiderCount(int &riderCount){
    this->riderCount = riderCount;
}

void Member::setRookie(Rider &rookie) {
    this->rookie = rookie;
}

void Member::setPoints(int &points) {
    this->points = points;
}

string Member::getUserName() {
    return userName;
}

Rider Member::getRookie() {
    return rookie;
}

RiderList* Member::getRiderList() {
    return riderList;
}

int Member::getRiderCount() {
    return riderCount;
}

int Member::getPoints() {
    return points;
}

string Member::toStringSmall() {
    string result;
    RiderNode* temp(riderList->getFirstPos());

    result += userName;
    result += " - ";
    result += to_string(points);

    result = fillSpaces(result, SPACE_USERNAME - result.length());

    while(temp != nullptr){
        result += temp->getData().toStringSmall();
        result += "| ";
        temp = temp->getNext();
    }

    if(!rookie.getNumber().empty()) {
        result += rookie.toStringSmall();
        result += "|";
    }

    return result;
}

Member &Member::operator=(const Member member1) {
    userName = member1.userName;
    riderList = member1.riderList;
    riderCount = member1.riderCount;
    rookie = member1.rookie;
    points = member1.points;
    return *this;
}
