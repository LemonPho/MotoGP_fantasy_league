#include "race-result-scraper.h"

RaceResultScraper::RaceResultScraper(RiderList *riderList, const string url) {
    int amountRiders = riderList->riderCount();

    riders = new Rider[amountRiders];
    this->url = url;
}

RaceResultScraper::~RaceResultScraper(){
    delete[] riders;
}

int RaceResultScraper::getRidersIndex() {
    return ridersIndex;
}

Rider RaceResultScraper::getRider(int index) {
    return riders[index];
}

string RaceResultScraper::getUrl() {
    return url;
}

string RaceResultScraper::getBuffer() {
    return buffer;
}

size_t RaceResultScraper::writeBuffer(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool RaceResultScraper::get() {
    CURL *curl;
    CURLcode result;

    curl = curl_easy_init();
    if(curl == nullptr){
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(result != CURLE_OK){
        cout << "Error getting from website: " << curl_easy_strerror(result) << endl;
        return false;
    }

    return true;
}

bool RaceResultScraper::saveHTML() {
    ofstream outFile(RACE_RESULT_HTML_FILE);

    if(!outFile){
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

bool RaceResultScraper::parseHTML() {
    LIBXML_TEST_VERSION
    htmlDocPtr doc;
    xmlNode* rootElement;
    xmlNode* tableElement;

    doc = htmlReadFile(RACE_RESULT_HTML_FILE, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if(doc == nullptr){
        return false;
    }

    //get html root element <html></html>
    rootElement = xmlDocGetRootElement(doc);

    //find the tbody element <tbody></tbody>
    tableElement = findTableBody(rootElement);
    //traverse table for saving results
    traverseTable(tableElement);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return true;
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

    //element is the table body
    if(strcmp(reinterpret_cast<const char *>(node->name), "tbody") == 0){
        return node;
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

    //for first case, since the tbody is sent, only used once
    if(strcmp(reinterpret_cast<const char *>(node->name), "tbody") == 0){
        node = node->children;
        return traverseTable(node);
    }

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
            riders[ridersIndex].setPosition(tempPosition);

            //load the next td
            return traverseTable(node->next);
        }

        //td has the number data
        if(strcmp(reinterpret_cast<const char *>(node->properties->children->content), "ms-table_cell ms-table_field--number") == 0){
            string tempNumber;

            tempNumber = reinterpret_cast<const char *>(node->children->next->children->content);

            //save number
            riders[ridersIndex].setNumber(tempNumber);


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
            riders[ridersIndex].setPoints(tempPoints);
            ridersIndex++;

            //load the next row
            return traverseTable(node->parent->next->next);
        }
    }

    //next element
    return traverseTable(node->next);
}