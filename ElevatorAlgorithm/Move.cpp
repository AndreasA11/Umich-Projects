/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Names
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

// Nondefault constructor
Move::Move(string commandString) : Move() {
    if (commandString == "") {
        isPass = true;
    }
    
    else {
        for (int i = 0; i < commandString.size(); i++) {
            char stringChar = commandString.at(i);
            stringChar = tolower(stringChar);
            
            if (stringChar == 'e') {
                elevatorId = commandString.at(i + 1);
                elevatorId -= '0';
            }
            if (stringChar == 'f') {
                targetFloor = commandString.at(i + 1);
                targetFloor -= '0';
            }
            if (stringChar == 'p') {
                isPickup = true;
            }
            if (stringChar == 's') {
                isSave = true;
            }
            if (stringChar == 'q') {
                isQuit = true;
            }
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    // checking for servicing move
    bool isServiceMove = false;
    if (!isPass && !isPickup && !isSave && !isQuit) {
        isServiceMove = true;
    }
    
    // checking cases for isValidMove
    if(isPass || isQuit || isSave) {
        return true;
    }
    else if (isPickup) {
        if(0 <= elevatorId && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing()) {
            return true;
        }
    }
    else if (isServiceMove) {
        if(0 <= elevatorId && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing()) {
            int currFloor = elevators[elevatorId].getCurrentFloor();
            if (0 <= targetFloor && targetFloor < NUM_FLOORS && targetFloor != currFloor) {
                return true;
            }
        }
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    int personMaxDist = 0;
    int personTargetFloor = 0;
    int i;
    int angerLevel = 0;
    int maxDist = 0;
    int dist = 0;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    
    // adding indices and incrementation of numPeopleTopPickUp
    for (i = 0; i < pickupList.size(); i++) {
        char stringPickup = pickupList.at(i);
        peopleToPickup[i] = stringPickup - '0';
        numPeopleToPickup++;
    }
    
    // configuring total satisfaction
    for (i = 0; i < numPeopleToPickup; i++) {
        angerLevel = pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        totalSatisfaction += (MAX_ANGER - angerLevel);
    }
    
    // calculating targetFloor
    for (i = 0; i < numPeopleToPickup; i++) {
        personTargetFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        dist = abs(personTargetFloor - currentFloor);
        if (dist > maxDist) {
            maxDist = dist;
            personMaxDist = i;
        }
    }
    
    targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[personMaxDist]).getTargetFloor();
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
