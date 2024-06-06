#include "race-result-list.h"

RaceResultList::RaceResultList() {
    this->errorMessage = nullptr;
}

RaceResultList::RaceResultList(ErrorMessage *errorMessage) {
    this->errorMessage = errorMessage;
}

RaceResultList::~RaceResultList(){}

void RaceResultList::pushRaceResult(RaceResult raceResult) {
    raceResults.push_back(raceResult);
}

void RaceResultList::eraseRaceResult(int index) {
    raceResults.erase(raceResults.begin() + index);
}

vector<RaceResult> RaceResultList::getRaceResults() {
    return raceResults;
}

void RaceResultList::readFromDisk(const string &filename, RiderList *riderList) {
    ifstream file(filename);
    string tempString, tempNumber;
    int i = 0, j = 0;

    RaceResult tempRaceResult;
    RiderManager tempRiderManager;
    Rider tempRider;
    RiderNode* node;


    if(!file.is_open()){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Wasn't possible to open the race results data file\n");
            return;
        }
    }

    getline(file, tempString, '\n');
    if(tempString.empty() || tempString == " "){
        return;
    }

    while(tempString != "\n" && !tempString.empty()){
        tempRaceResult = RaceResult(errorMessage);
        tempRaceResult.setName(tempString);
        getline(file, tempString, '\n');
        tempRaceResult.setIsSprint(stoi(tempString));

        const int *points = tempRaceResult.getIsSprint() ? POINTS_SPR : POINTS_RAC;
        const int limitPoints = tempRaceResult.getIsSprint() ? LIMIT_SPR : LIMIT_RAC;

        getline(file, tempString, '\n');
        j = stoi(tempString);
        for(i = 0; i < j; i++){
            getline(file, tempString, '|');
            tempRider.setNumber(tempString);
            tempRiderManager.setPosition(i+1);
            if(i < limitPoints){
                tempRiderManager.setPoints(points[i]);
            } else {
                tempRiderManager.setPoints(0);
            }
            tempRiderManager.setRider(tempRider);
            node = riderList->retrievePos(tempRiderManager);
            if(!node){
                if(errorMessage){
                    errorMessage->addErrorMessage("Could not find the rider data for #" + tempNumber + "\n");
                }
                string tempName = "Rider #" + tempRider.getNumber() + " not found";
                tempRider.setFirstName(tempName);
            } else {
                tempRiderManager.setRider(node->getData().getRider());
            }

            tempRaceResult.pushRiderPosition(tempRiderManager);

            tempRider = Rider();
            tempRiderManager = RiderManager();
        }
        raceResults.push_back(tempRaceResult);
        getline(file, tempString, '\n');
        getline(file, tempString, '\n');
        cout << "pause" << endl;
    }
}

void RaceResultList::writeToDisk(const string &filename) {
    ofstream file(filename, ios::out);
    string tempString;

    if(!file.is_open()){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("There was an error trying to open the race results data file\n");
            return;
        }
    }

    tempString = toStringDisk();
    file << tempString;

    file.close();
}

string RaceResultList::toString() {
    string result = "";

    if(raceResults.empty()){
        return "No races saved yet\n";
    }

    for(size_t i = 0; i < raceResults.size(); i++){
        result += "-----------------------------------------------------------------------------------------------\n";
        result += raceResults[i].toString();
    }

    return result;
}

string RaceResultList::toStringSmallWithIndex() {
    string result = "";

    if(raceResults.empty()){
        return "No races saved yet\n";
    }

    for(size_t i = 0; i < raceResults.size(); i++){
        result += to_string(i) + " ----------------------------------------------------------------------------------------------- " + to_string(i) + "\n";
        result += raceResults[i].toStringSmall();
    }

    return result;
}

string RaceResultList::toStringDisk() {
    string result;
    for(int i = 0; i < raceResults.size(); i++){
        result += raceResults[i].toStringDisk();
    }
    result += "\n";
    return result;
}

RaceResultList &RaceResultList::operator=(RaceResultList raceResultList) {
    this->raceResults = raceResultList.raceResults;
    this->errorMessage = raceResultList.errorMessage;

    return *this;
}



