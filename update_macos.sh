#!/bin/bash

#pull changes from github
echo "retrieving the changes from github"
git clone -b MotoGP_Fantasy_League_Windows https://github.com/BenitoCamelo2/MotoGP_fantasy_league.git || { echo "getting the changes failed"; exit 1; }

#build new program file
echo "building new program"
g++ $(xml2-config --cflags) -IMotoGP_fantasy_league/include MotoGP_fantasy_league/src/*.cpp -o "MotoGP Fantasy League" -lncurses $(xml2-config --libs) -lcurl || { echo "Building the program failed"; exit 1; }

echo "Build successful, open the home directory in finder and copy the new program executable and paste it wherever you like to have it"