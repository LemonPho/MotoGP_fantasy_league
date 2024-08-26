#include "race-result-scraper.h"

RaceResultScraper::RaceResultScraper() {
    tempRider = RiderManager();
    url = "https://www.motorsport.com/motogp/results";
    errorMessage = nullptr;
}

RaceResultScraper::RaceResultScraper(ErrorMessage *errorMessage) {
    tempRider = RiderManager();
    this->url = "https://www.motorsport.com/motogp/results";
    this->errorMessage = errorMessage;
}

RaceResultScraper::RaceResultScraper(const string url, ErrorMessage *errorMessage) {
    tempRider = RiderManager();
    this->url = url;
    this->errorMessage = errorMessage;
}

RaceResultScraper::~RaceResultScraper()= default;

RaceResult RaceResultScraper::getRaceResult() {
    return raceResult;
}

bool RaceResultScraper::getUrlIsSprint() {
    CURL *curl;
    CURLcode result;
    string redirectUrl = "";
    string tempString;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl == nullptr){
        return "";
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    result = curl_easy_perform(curl);

    if(result == CURLE_OK){
        char* tempRedirectUrl;
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &tempRedirectUrl);
        redirectUrl = tempRedirectUrl;
    } else {
        if(errorMessage){
            errorMessage->addErrorMessage("Error getting url from website: " + string(curl_easy_strerror(result)) + "\n");
        }
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    for(size_t i = redirectUrl.length()-3; i < redirectUrl.length(); i++){
        tempString += redirectUrl[i];
    }

    if(tempString == "SPR"){
        return true;
    } else {
        return false;
    }
}

string RaceResultScraper::getUrl() {
    return url;
}

string RaceResultScraper::getBuffer() {
    return buffer;
}

string RaceResultScraper::trimSpaces(string source) {
    string result;
    size_t start=source.length()+1, end;

    for(size_t i = 0, j = 0; i < source.length(); i++){
        if(source[i] != ' ' && source[i] != '\n' && source[i] != '\r'){
            start = i;
            break;
        }
    }

    for(size_t i = source.length()-1; i >= start; i--){
        if(source[i] != ' ' && source[i] != '\n' && source[i] != '\r'){
            end = i+1;
            break;
        }
    }

    result.resize(end-start);

    for(size_t i = start, j = 0; i <= end; i++, j++){
        result[j] = source[i];
    }

    return result;
}

size_t RaceResultScraper::writeBuffer(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t RaceResultScraper::writeNothing(void *contents, size_t size, size_t nmemb, void *userp) {
    return 0;
}

bool RaceResultScraper::generateRaceResult(RiderList *riderList) {
    if(!retrieveResults()){

        return false;
    }

    if(!saveHTML()){

        return false;
    }

    if(!parseHTML(riderList)){
        return false;
    }
    raceResult.setIsSprint(getUrlIsSprint());

    return true;
}

bool RaceResultScraper::retrieveResults() {
    CURL *curl;
    CURLcode result;

    curl = curl_easy_init();
    if(curl == nullptr){
        if(errorMessage){
            errorMessage->addErrorMessage("CURL failed to start\n");
        }
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if(result != CURLE_OK){
        if(errorMessage){
            errorMessage->addErrorMessage("Error getting information from website: " + string(curl_easy_strerror(result)) + "\n");
        }
        return false;
    }

    return true;
}

bool RaceResultScraper::saveHTML() {
    ofstream outFile(RACE_RESULT_HTML_FILE);

    if(!outFile){
        if(errorMessage){
            errorMessage->addErrorMessage("Error creating the temporary html file, be sure the program has the correct permisions to create files\n");
        }
        return false;
    }

    outFile << buffer;
    outFile.close();

    return true;
}

bool RaceResultScraper::deleteHTML() {
    ifstream inFile(RACE_RESULT_HTML_FILE);

    if(!inFile){
        inFile.close();
        return false;
    }

    inFile.close();
    std::remove(RACE_RESULT_HTML_FILE);

    return true;
}

bool RaceResultScraper::parseHTML(RiderList* riderList) {
    LIBXML_TEST_VERSION
    htmlDocPtr doc;
    xmlNode* rootElement;
    xmlNode* tableElement;

    doc = htmlReadFile(RACE_RESULT_HTML_FILE, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if(doc == nullptr){
        if(errorMessage){
            errorMessage->addErrorMessage("There was an issue trying to read the html file\n");
        }
        return false;
    }

    //get html root element <html></html>
    rootElement = xmlDocGetRootElement(doc);
    if(!rootElement){
        if(errorMessage){
            errorMessage->addErrorMessage("Could not find root element of html document\n");
        }
        return false;
    }

    //find the tbody element <tbody></tbody>
    tableElement = findTableBody(rootElement);
    if(!tableElement || tableElement == rootElement){
        if(errorMessage){
            errorMessage->addErrorMessage("Could not find the table in the retrieved race results\n");
        }
        return false;
    }
    //traverse table for saving results
    generateRiderPositions(tableElement, riderList);

    //find race title
    findRaceTitle(rootElement);
    if(raceResult.getName().empty()){
        if(errorMessage != nullptr){
            errorMessage->addErrorMessage("Couldn't find the race title\n");
        }
        return false;
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return true;
}

xmlNode* RaceResultScraper::findRaceTitle(xmlNode *node) {
    //base cases
    if(!raceResult.getName().empty()){
        return nullptr;
    }

    if(node == nullptr){
        return nullptr;
    }

    //skip styles
    if(node->name != nullptr){
        if(strcmp(reinterpret_cast<const char *>(node->name), "style") == 0){
            return nullptr;
        }
    }

    //find race title
    if(node->name != nullptr && strcmp(reinterpret_cast<const char *>(node->name), "h1") == 0){
        if(node->properties && node->properties->children && node->properties->children->content){
            if(strcmp(reinterpret_cast<const char *>(node->properties->children->content), "ms-select__option-title text-h3 font-bold m-0") == 0){
                string tempName = reinterpret_cast<const char *>(node->children->content);
                tempName = trimSpaces(tempName);
                raceResult.setName(tempName);
                return nullptr;
            }
        }
    }

    //go deeper in branch
    xmlNode* newNode = findRaceTitle(node->children);
    if(newNode != nullptr){
        return findRaceTitle(node->children);
    }

    //go next branch
    return findRaceTitle(node->next);
}

xmlNode* RaceResultScraper::findTableBody(xmlNode *node) {
    //end of branch
    if(node == nullptr){
        return nullptr;
    }

    //here we skip style tags, some have so much text that it causes a segmentation fault
    if(node->name != nullptr){
        if(strcmp(reinterpret_cast<const char *>(node->name), "style") == 0){
            return nullptr;
        }
    }

    //skpi script tags
    if(node->name != nullptr){
        if(strcmp(reinterpret_cast<const char *>(node->name), "script") == 0){
            return nullptr;
        }
    }

    //element is the table body
    if(strcmp(reinterpret_cast<const char *>(node->name), "tbody") == 0){
        return node->children;
    }

    //if element has children, enter the element
    xmlNode* result = findTableBody(node->children);
    if (result != nullptr) {
        return result;
    }

    //get next element
    return findTableBody(node->next);
}

xmlNode* RaceResultScraper::traverseTable(xmlNode *node) {
    //base case
    if(node == nullptr){
        return nullptr;
    }

    /*
    //for first case, since the tbody is sent, only used once
    if(strcmp(reinterpret_cast<const char *>(node->name), "tbody") == 0){
        node = node->children;
        return traverseTable(node);
    }*/

    //if the element is a row, enter the row data
    if(strcmp(reinterpret_cast<const char *>(node->name), "tr") == 0){
        node = node->children;
        return traverseTable(node);
    }

    //check if element is td
    if(strcmp(reinterpret_cast<const char *>(node->name), "td") == 0){
        //td has the position data
        if(strcmp(reinterpret_cast<const char *>(node->properties->children->content), "ms-table_cell ms-table_field--pos") == 0){
            int tempPosition;

            //check for dnf
            if(strcmp(reinterpret_cast<const char *>(node->children->next->children->content), "dnf") == 0){
                tempPosition = 0;
            } else {
                tempPosition = atoi(reinterpret_cast<const char *>(node->children->next->children->content));
            }

            //saving position
           tempRider.setPosition(tempPosition);

            //load the next td
            return traverseTable(node->next);
        }

        //td has the number data
        if(strcmp(reinterpret_cast<const char *>(node->properties->children->content), "ms-table_cell ms-table_field--number") == 0){
            string tempNumber;

            tempNumber = reinterpret_cast<const char *>(node->children->next->children->content);
            cout << reinterpret_cast<const char *>(node->children->next->children->content) << endl;

            //save number
            tempRider.getRider().setNumber(tempNumber);


            //load the next td
            return traverseTable(node->next);
        }

        //td has the points data
        if(strcmp(reinterpret_cast<const char *>(node->properties->children->content), "ms-table_cell ms-table_field--points") == 0){
            int tempPoints;

            //when rider got 0 points this is equal to nullptr
            if(node->children->next->children == nullptr){
                tempPoints = 0;
            } else {
                tempPoints = atoi(reinterpret_cast<const char *>(node->children->next->children->content));
            }

            //saving points
            tempRider.setPoints(tempPoints);

            raceResult.pushRiderPosition(tempRider);
            tempRider = RiderManager();
            //load the next row
            return traverseTable(node->parent->next->next);
        }
    }

    //next element
    return traverseTable(node->next);
}

void RaceResultScraper::addRacePointsToRiderList(RiderList* riderList) {
    RiderList* tempRiderList = new RiderList();
    RiderNode* tempRiderNode = new RiderNode();
    Rider tempRider;
    RiderManager tempRiderManager;
    string tempNumber;
    int tempPoints, tempPosition;
    for(int i = 0; i < raceResult.getRiderPositions().size(); i++){
        tempNumber = raceResult.getRiderPositions()[i].getRider().getNumber();
        tempPoints = raceResult.getRiderPositions()[i].getPoints();
        tempPosition = raceResult.getRiderPositions()[i].getPosition();

        tempRider.setNumber(tempNumber);
        tempRiderManager.setRider(tempRider);
        tempRiderNode = riderList->retrievePos(tempRiderManager);

        if(tempRiderNode == nullptr){
            if(errorMessage != nullptr){
                errorMessage->addErrorMessage("Couldn't find data for rider #" + tempRider.getNumber() + "\n");
            }
            return;
        } else {
            tempRiderManager = tempRiderNode->getData();
            tempRiderManager.setPoints(tempPoints);
            tempRiderManager.setPosition(tempPosition);
        }
    }

}

void RaceResultScraper::generateRiderPositions(xmlNode* node, RiderList *riderList) {
    traverseTable(node);

    Rider tempRider;
    RiderNode* riderNode;
    for(size_t i = 0;i < raceResult.getRiderPositions().size(); i++){
        riderNode = riderList->retrievePos(raceResult.getRiderPositions()[i]);
        if(!riderNode){
            errorMessage->addErrorMessage("Competitor with #" + raceResult.getRiderPositions()[i].getRider().getNumber() + " was not found in the rider list, be sure to have him added in the list of riders");
            tempRider = Rider();
        } else {
            tempRider = riderNode->getData().getRider();
        }
        raceResult.setRider(tempRider, i);
    }
}


