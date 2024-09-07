#!/bin/bash

#pull changes from github
echo "retrieving the changes from github"
git clone -b MotoGP_Fantasy_League_macOS https://github.com/BenitoCamelo2/MotoGP_fantasy_league.git || { echo "getting the changes failed"; exit 1; }

#build new program file
echo "building new program"
g++ $(xml2-config --cflags) -IMotoGP_fantasy_league/include MotoGP_fantasy_league/src/*.cpp -o "MotoGP Fantasy League" -lncurses $(xml2-config --libs) -lcurl || { echo "Building the program failed"; exit 1; }

echo "${GREEN}Build successful${NC}, moving program to downloads folder"

mv "MotoGP Fantasy League" /Applications

echo "You may close the program, updated program was placed in the applications folder"