//
// Created by mishu on 6/2/2024.
//

#ifndef MOTOGP_FANTASY_LEAGUE_ERROR_MESSAGE_H
#define MOTOGP_FANTASY_LEAGUE_ERROR_MESSAGE_H

#include <iostream>

using namespace std;

class ErrorMessage{
private:
    string message;
public:
    ErrorMessage();

    void setErrorMessage(string errorMessage);
    void addErrorMessage(const string& errorMessage);
    string getErrorMessage();
    bool isEmpty();
};

#endif //MOTOGP_FANTASY_LEAGUE_ERROR_MESSAGE_H
