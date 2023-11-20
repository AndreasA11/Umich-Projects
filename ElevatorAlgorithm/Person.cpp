/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Andreas, Isaac, Sofia, Annika
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>
 
using namespace std;
 
Person::Person(string inputString) : Person() {
    //going through each char in the string and checking if it is a letter or number by the ASCII range.
    //If it is a number subtract by 48, which will convert ASCII to number.
    for(int i = 0; i < inputString.size(); i++) {
        if(inputString.at(i) >= 48 && inputString.at(i) <= 57) {
            inputString.at(i) -= 48;
        }
    }
    //checks if inputString[1] is a number(between 0 and 9), if it is turn will be a double digit number so turn combines inputString[0] and inputString[1], rest of variables adjusted.
    // else turn is single digit so turn is just inputString[0], rest of variables adjusted
    if(inputString.at(1) >= 0 && inputString.at(1) <= 9) {
        turn = inputString.at(0) * 10 + inputString.at(1);
        currentFloor = inputString.at(3);
        targetFloor = inputString.at(5);
        angerLevel = inputString.at(7);
    } else {
    turn = inputString.at(0);
    currentFloor = inputString.at(2);
    targetFloor = inputString.at(4);
    angerLevel = inputString.at(6);
    }
}
 
bool Person::tick(int currentTime) {
    if(currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel++;
    }
    if(angerLevel == MAX_ANGER) {
        return true;
    } else {
        return false;
    }
}
 
void Person::print(ostream &outs) {
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;
}
 
//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////
 
Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}
 
int Person::getTurn() const {
    return turn;
}
 
int Person::getCurrentFloor() const {
    return currentFloor;
}
 
int Person::getTargetFloor() const {
    return targetFloor;
}
 
int Person::getAngerLevel() const {
    return angerLevel;
}
 
ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
