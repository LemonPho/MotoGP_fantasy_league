#include <iostream>
#include <utility>
#include "race-result.h"

RaceResult::RaceResult() {
    name = "";
    isSprint = false;

    errorMessage = nullptr;
}

RaceResult::RaceResult(ErrorMessage *errorMessage) {
    this->errorMessage = errorMessage;
}

RaceResult::RaceResult(vector<RiderManager> riderList, string name, bool isSprint, ErrorMessage *errorMessage) {
    riderPositions = std::move(riderList);
    this->name = std::move(name);
    this->isSprint = isSprint;
    this->errorMessage = errorMessage;
}

RaceResult::~RaceResult(){}

void RaceResult::setName(const string &name) {
    this->name = name;
}

void RaceResult::setIsSprint(const bool &isSprint) {
    this->isSprint = isSprint;
}

void RaceResult::setRider(Rider rider, size_t index) {
    riderPositions[index].setRider(rider);
}

void RaceResult::setRiderPositions(vector<RiderManager> riderPositions) {
    this->riderPositions = std::move(riderPositions);
}

vector<RiderManager> RaceResult::getRiderPositions() {
    return riderPositions;
}

string& RaceResult::getName() {
    return name;
}

bool& RaceResult::getIsSprint() {
    return isSprint;
}

bool RaceResult::updateRiderList(RiderList *riderList) {
    RiderNode* node = new RiderNode();
    int points;
    bool changes = false;

    for(size_t i = 0; i < riderPositions.size(); i++){
        node = riderList->retrievePos(riderPositions[i]);
        if(node == nullptr){
            if(errorMessage != nullptr){
                errorMessage->addErrorMessage("Couldn't find rider #" + riderPositions[i].getRider().getNumber() + " in the rider list\n");
            }
        } else {
            changes = true;
            points = node->getData().getPoints() + riderPositions[i].getPoints();
            node->getDataReference()->setPoints(points);
        }
    }

    return changes;
}

//if it returns anything than 0 it means that the rider associated to the number was going to have < 0 points
bool RaceResult::deleteRaceResult(RiderList* riderList) {
    RiderNode* tempNode = new RiderNode();
    RiderManager tempRiderManager;
    Rider tempRider;
    int tempPoints, finalPoints;
    string tempNumber;

    for(size_t i = 0; i < riderPositions.size(); i++){
        tempPoints = riderPositions[i].getPoints();
        tempNumber = riderPositions[i].getRider().getNumber();
        tempRider.setNumber(tempNumber);
        tempRiderManager.setRider(tempRider);
        tempNode = riderList->retrievePos(tempRiderManager);
        if(tempNode){
            finalPoints = tempNode->getDataReference()->getPoints() - tempPoints;
            tempNode->getDataReference()->setPoints(finalPoints);
        } else {
            return false;
        }
    }

    return true;
}

string RaceResult::toString(){
    string tempString;
    tempString = name;
    if(isSprint){
        tempString += " Sprint";
    }
    tempString += "\n";
    for(size_t i = 0; i < riderPositions.size(); i++){
        tempString += riderPositions[i].toString() + "\n";
    }

    return tempString;
}

string RaceResult::toStringSmall() {
    string tempString;
    size_t limit = AMOUNT_RIDERS_SMALL_RESULTS;

    if(riderPositions.size() < limit){
        limit = riderPositions.size();
    }

    tempString = name;
    if(isSprint){
        tempString += " Sprint";
    }
    tempString += "\n";

    for(size_t i = 0; i < limit; i++){
        tempString += to_string(i+1) + ". ";
        tempString += riderPositions[i].toStringSmall(true) + "\n";
    }

    return tempString;
}

string RaceResult::toStringVerySmall(){
    string tempString;

    tempString = name;
    if(isSprint){
        tempString += " Sprint";
    }

    return tempString;
}

string RaceResult::toStringDisk(){
    string tempString;

    tempString = name + "\n";
    tempString += to_string(isSprint) + "\n";
    tempString += to_string(riderPositions.size()) + "\n";

    for(size_t i = 0; i < riderPositions.size(); i++){
        tempString += riderPositions[i].getRider().getNumber() + "|";
    }

    tempString += "\n";

    return tempString;
}

RaceResult& RaceResult::operator=(RaceResult raceResult) {
    if(this == &raceResult){
        return *this;
    }

    riderPositions = raceResult.riderPositions;
    name = raceResult.name;
    isSprint = raceResult.isSprint;

    return *this;
}

void RaceResult::pushRiderPosition(RiderManager newRider) {
    riderPositions.push_back(newRider);
}
