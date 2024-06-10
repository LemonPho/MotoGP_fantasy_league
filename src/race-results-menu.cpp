#include "race-results-menu.h"

RaceResultsMenu::RaceResultsMenu(RiderList *riderList, MemberList *memberList, string seasonName) {
    this->raceResultList = RaceResultList(&errorMessage);
    this->raceResultList.readFromDisk(seasonName + '-' + RACE_DATA, riderList);

    this->seasonName = seasonName;

    this->riderList = new RiderList();
    this->riderList->deepCopy(riderList);
    this->riderList->setErrorMessage(&errorMessage);

    this->memberList = new MemberList();
    this->memberList->deepCopy(memberList);
    this->memberList->setErrorMessage(&errorMessage);
    menu();
}

RaceResultsMenu::~RaceResultsMenu() {}

void RaceResultsMenu::menu() {
    string option;
    bool exit = false;
    int changes = 0;

    while(!exit){
        system(CLEAR);
        cout << "Race Results Menu" << endl;

        if(!errorMessage.isEmpty()){
            cout << endl << errorMessage.getErrorMessage() << endl;
            errorMessage.setErrorMessage("");
        }

        cout << "1. Automatically Load Most Recent Race Result" << endl;
        cout << "2. Load Race Result with Results Link" << endl;
        cout << "3. Manually add Race Result" << endl;
        cout << "4. Manually add Sprint Race Result" << endl;
        cout << "5. View Race Results" << endl;
        cout << "6. Delete Race Result" << endl;
        cout << "7. Exit" << endl;
        cout << "Option: " << endl;
        cout << "-> ";
        cin >> option;
        switch(optionSelector(option)){
            case AUTOMATIC_ADD_RESULT: {
                changes += addRaceResultAutomatic(false);
                break;
            }

            case AUTOMATIC_ADD_RESULT_LINK: {
                changes += addRaceResultAutomatic(true);
                break;
            }

            case MANUAL_ADD_RACE_RESULT: {
                changes += addRaceResultManual(false);
                break;
            }

            case MANUAL_ADD_SPRINT_RESULT: {
                changes += addRaceResultManual(true);
                break;
            }

            case VIEW_RACE_RESULTS: {
                showRaceResults();
                clearBuffer();
                enterToContinue();
                break;
            }

            case DELETE_RACE_RESULT: {
                changes += deleteRaceResult();
                break;
            }

            case EXIT_RACE_RESULT_MENU: {
                int saveChangesOption;
                if(changes){
                    cout << "Would you like to save the changes made? (1. Yes, 2. No)" << endl;
                    cout << "-> ";
                    cin >> saveChangesOption;
                    if(saveChangesOption == 1){
                        raceResultList.writeToDisk(seasonName + '-' + RACE_DATA);
                        riderList->writeToDisk(seasonName + '-' + RIDER_DATA);
                        memberList->writeToDisk(seasonName + '-' + MEMBER_DATA);
                    }
                }
                delete riderList;
                delete memberList;
                exit = true;
                break;
            }

            default:{
                errorMessage.addErrorMessage("Invalid option\n");
                break;
            }
        }
    }
}

bool RaceResultsMenu::addRaceResultAutomatic(bool link) {
    system(CLEAR);
    string url;
    bool changes = false;

    RaceResultScraper raceResultScraper;

    if(link){
        cout << "Add Race Results Automatic" << endl;
        cout << "Paste the link of the race result from motorsport.com" << endl;
        cout << "->";
        cin >> url;
        raceResultScraper = RaceResultScraper(url, &errorMessage);
    } else {
        raceResultScraper = RaceResultScraper(&errorMessage);
    }

    if(!raceResultScraper.generateRaceResult(riderList)){
        return changes;
    }

    system(CLEAR);
    int confirmChanges;
    cout << "Retrieved race result" << endl;
    cout << raceResultScraper.getRaceResult().toString();
    cout << "1. Accept race result" << endl;
    cout << "2. Cancel race result" << endl;
    cout << "Option: ";
    cin >> confirmChanges;

    if(confirmChanges == 1){
        raceResultList.pushRaceResult(raceResultScraper.getRaceResult());
        raceResultScraper.getRaceResult().updateRiderList(riderList);
        memberList->updateMembersRiders(riderList);
        memberList->updateMembersPoints();
        changes = true;
    }

    if(!raceResultScraper.deleteHTML()){
        cout << "Error deleting the temporary html file, result was saved" << endl;
        clearBuffer();
        enterToContinue();
        return changes;
    }

    return changes;
}

bool RaceResultsMenu::addRaceResultManual(bool isSprint) {
    system(CLEAR);

    RaceResult raceResult;
    RiderNode* node = riderList->getFirstPos();
    Rider tempRider;
    RiderManager tempRiderManager;
    int position, option;
    const int *points = isSprint ? POINTS_SPR : POINTS_RAC;
    const int pointsLimit = isSprint ? LIMIT_SPR : LIMIT_RAC;
    string line, raceTitle;


    cout << "Add Race Results" << endl;
    cout << "Input the race title" << endl;
    clearBuffer();
    getline(cin, raceTitle, '\n');
    raceResult.setName(raceTitle);
    raceResult.setIsSprint(isSprint);

    while(node != nullptr){
        line = node->getData().toStringSmallFullName();
        tempRiderManager = node->getData();
        cout << line << endl;
        cout << "Input final race position" << endl;
        cout << "->";
        cin >> position;
        position--;
        if(position <= pointsLimit && position >= 0) {
            tempRiderManager.setPoints(points[position-1]);
            raceResult.getRiderPositions().push_back(tempRiderManager);
        }
        node = node->getNext();
    }
    delete points;
    cout << raceResult.toString();
    cout << "1. Accept results" << endl;
    cout << "2. Decline results" << endl;
    cout << "Option: ";
    cin >> option;
    if(option == 1){
        return false;
    } else {
        raceResult.updateRiderList(riderList);
        return true;
    }
}

void RaceResultsMenu::showRaceResultsSmall() {
    system(CLEAR);
    cout << raceResultList.toStringSmallWithIndex();
}

void RaceResultsMenu::showRaceResults() {
    system(CLEAR);
    cout << raceResultList.toString();
}

bool RaceResultsMenu::deleteRaceResult() {
    int index;

    showRaceResultsSmall();
    cout << "Input the index of the race you would like to delete" << endl;
    cout << "-> ";
    cin >> index;

    if(index < 0 || index > raceResultList.getRaceResults().size()){
        errorMessage.addErrorMessage("Invalid index, please try again\n");
        return false;
    }

    raceResultList.getRaceResults()[index].deleteRaceResult(riderList);
    raceResultList.eraseRaceResult(index);
    return true;
}

int RaceResultsMenu::optionSelector(std::string option) {
    if(option == "1") return AUTOMATIC_ADD_RESULT;
    if(option == "2") return AUTOMATIC_ADD_RESULT_LINK;
    if(option == "3") return MANUAL_ADD_RACE_RESULT;
    if(option == "4") return MANUAL_ADD_SPRINT_RESULT;
    if(option == "5") return VIEW_RACE_RESULTS;
    if(option == "6") return DELETE_RACE_RESULT;
    if(option == "7") return EXIT_RACE_RESULT_MENU;
    return 0;
}