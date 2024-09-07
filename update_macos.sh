#!/bin/bash

#pull changes from github
echo "retrieving the changes from github"
git pull origin MotoGP_Fantasy_League_Windows || { echo "getting the changes failed"; exit 1; }

#build new program file
echo "building new program"
g++ $(xml2-config --cflags) -Iinclude src/*.cpp -o "MotoGP Fantasy League" -lncurses $(xml2-config --libs) -lcurl

echo "Build successful, you may open the program"