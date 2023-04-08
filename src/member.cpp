#include "member.h"

Member::Member() {
    userName = "";
    riderList = new RiderList();
    points = 0;
}

Member::Member(const Member &member) {
    this->userName = member.userName;
    this->riderList = member.riderList;
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

void Member::setPoints(int &points) {
    this->points = points;
}

string Member::getUserName() {
    return userName;
}

RiderList* Member::getRiderList() {
    return riderList;
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

    return result;
}

Member &Member::operator=(const Member &member) {
    userName = member.userName;
    riderList = member.riderList;
    points = member.points;
    return *this;
}

bool Member::operator==(const Member &member){
    return userName == member.userName;
}
