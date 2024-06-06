#include "rider-manager.h"

RiderManager::RiderManager() {
    rider = Rider();
    points = 0;
    position = 0;
}

RiderManager::~RiderManager() {
    rider = Rider();
    points = 0;
    position = 0;
}

Rider& RiderManager::getRider() {
    return rider;
}

int RiderManager::getPoints() {
    return points;
}

int RiderManager::getPosition() {
    return position;
}

void RiderManager::setRider(Rider rider) {
    this->rider = rider;
}

void RiderManager::setPoints(int points) {
    if(points >= 0){
        this->points = points;
    }
}

void RiderManager::setPosition(int position){
    this->position = position;
}

string RiderManager::toString(){
    string result;
    string name = rider.getFirstName() + " " + rider.getLastName();

    result += fillSpaces(to_string(position), SPACE_POSITION - to_string(position).length());
    result += "|";
    result += fillSpaces(rider.getNumber(), SPACE_NUMBER - rider.getNumber().length());
    result += "|";
    result += fillSpaces(name, SPACE_NAME - name.length());
    result += "|";
    result += fillSpaces(to_string(points), SPACE_POINTS - to_string(points).length());
    result += "|";
    result += fillSpaces(rider.getCountry(), SPACE_COUNTRY - rider.getCountry().length());
    result += "|";
    result += fillSpaces(rider.getTeam(), SPACE_TEAM - rider.getTeam().length());
    result += "|";
    return result;
}

string RiderManager::toStringIndexed(int index) {
    string result;
    string name = rider.getFirstName() + " " + rider.getLastName();

    result = to_string(index);
    result += " |";
    result += fillSpaces(name, SPACE_NAME - name.length());
    result += "|";
    result += fillSpaces(to_string(points), SPACE_POINTS - to_string(points).length());
    result += "|";
    result += fillSpaces(rider.getCountry(), SPACE_COUNTRY - rider.getCountry().length());
    result += "|";
    result += fillSpaces(rider.getTeam(), SPACE_TEAM - rider.getTeam().length());
    result += "|";

    return result;
}

string RiderManager::toStringSmall(bool spacing) {
    string result;

    result += rider.getFirstName()[0];
    result += ".";
    for(int i = 0; i < 3; i++){
        result += rider.getLastName()[i];
    }
    result += " - ";
    result += to_string(points);

    if(spacing) {
        result = fillSpaces(result, SPACE_PRINT_SMALL - result.length());
    }

    return result;
}

string RiderManager::toStringSmallFullName() {
    string result;

    result = rider.getFirstName();
    result += " ";
    result += rider.getLastName();

    return result;
}

string RiderManager::toStringDisk() {
    string result;

    result += rider.getNumber();
    result += "|";
    result += rider.getFirstName();
    result += "|";
    result += rider.getLastName();
    result += "|";
    result += rider.getCountry();
    result += "|";
    result += rider.getTeam();
    result += "|";
    result += to_string(points);
    result += "|";
    return result;
}

RiderManager& RiderManager::operator=(const RiderManager &riderManager){
    rider = riderManager.rider;
    points = riderManager.points;
    position = riderManager.position;

    return *this;
}

bool RiderManager::operator==(const RiderManager &riderManager) {
    return this->rider == riderManager.rider;
}

bool RiderManager::operator!=(const RiderManager &riderManager){
    return this->rider != riderManager.rider;
}

bool RiderManager::operator<=(const RiderManager &riderManager) {
    return this->rider <= riderManager.rider;
}

bool RiderManager::operator>=(const RiderManager &riderManager) {
    return this->rider >= riderManager.rider;
}

bool RiderManager::operator<(const RiderManager &riderManager) {
    return this->rider < riderManager.rider;
}

bool RiderManager::operator>(const RiderManager &riderManager) {
    return this->rider > riderManager.rider;
}