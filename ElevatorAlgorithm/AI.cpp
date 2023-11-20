/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include "AI.h"
#include <cassert>
#include <cstdlib>
#include <vector>
 
// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core
string getAIMoveString(const BuildingState& buildingState) {
//------------ AI STRING INTIALIZATIONS --------------
    string AIMoveToFloor = "e0f0";
    string AIPickupMove = "e0p";
    string AIPassMove = "";
    string AIChosenMove;
    
//------------- INITIAL CHECKS ---------------
    
//CHECKING TO SEE WHICH ELEVATORS ARE SERVICING ----
    int countServicing = 0;
    bool isAvailable[NUM_ELEVATORS] = {false};
    vector<int> listServicing;
    vector<int> listElevatorsAvail;
    int indexOfElevator = 0;
    
    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        
        //checking elevators
        _Elevator elevator = buildingState.elevators[i];
    
        //checking to see if elevator is MOVING
        if (elevator.isServicing) {
            ++countServicing;
            ++indexOfElevator;
            listServicing.push_back(i);
        }
                
        //checking to see if elevator is IDLE and adding it to an array
        //in order to keep track of which elevators are avaliable
        if (!elevator.isServicing) {
            isAvailable[indexOfElevator] = true;
            listElevatorsAvail.push_back(indexOfElevator);
            ++indexOfElevator;
        }
    }

 
//DECIDING WHICH FLOOR TO SEND IT TO ---------------
    // array to hold ea floors total anger levels
    int allFloorAngerLvls[NUM_FLOORS] = {0};
    int personAngerLvl = 0;
    int floorTotalAngerLevel = 0;
    char priorityFloorChar = '0';
    
    // anger multiplier
    int angerMultiplier[MAX_ANGER];
    for (int i = 0; i < MAX_ANGER; i++) {
        angerMultiplier[i] = pow(i, 2);
    }
    
    // storing anger levels of ea floor
    for (int f = 0; f < NUM_FLOORS; f++) {
        for (int p = 0; p < buildingState.floors[f].numPeople; p++) {
            personAngerLvl = buildingState.floors[f].people[p].angerLevel;
            floorTotalAngerLevel += angerMultiplier[personAngerLvl];
            allFloorAngerLvls[f] = floorTotalAngerLevel;
        }
        floorTotalAngerLevel = 0;
    }
          
    // comparing anger levels of ea floor, determine priority floor
    vector <int> priorityFloor;
    int priority1Anger = 0;
    int priority2Anger = 0;
        
    for (int f = 0; f < NUM_FLOORS; f++) {
        if (allFloorAngerLvls[f] > priority1Anger) {
            priorityFloor.insert(priorityFloor.begin(), f);
            priority1Anger = allFloorAngerLvls[f];
        }
        else if (allFloorAngerLvls[f] <= priority1Anger && allFloorAngerLvls[f] > priority2Anger) {
            priorityFloor.insert(priorityFloor.begin() + 1, f);
            priority2Anger = allFloorAngerLvls[f];
        }
        else {
            int numWaiting = buildingState.floors[f].numPeople;
            if (allFloorAngerLvls[f] == priority2Anger &&  numWaiting > 0) {
                priorityFloor.push_back(f);
            }
            if (allFloorAngerLvls[f] < priority2Anger &&
                allFloorAngerLvls[f] > allFloorAngerLvls[priorityFloor.back()]) {
                priorityFloor.push_back(f);
            }
        }
    }
    
 // if floors have people but with zero anger

    for (int f = 0; f < NUM_FLOORS; f++) {
        if (buildingState.floors[f].numPeople > 0 && allFloorAngerLvls[f] == 0) {
            priorityFloor.push_back(f);
        }
    }
    
    
//MOVE CHECKS BOOLS -------------------------
    bool isAIMoveToFloor = false;
    bool isAIPickupMove = false;
    bool isAIPass = false;
    
// MOVE CHECKS -------------------------------------------------
 
//IF ALL ELEVATORS ARE SERVICING (countServicing = 3) ---- Pass
    if (countServicing == 3) {
        isAIPass = true;
    }
    //IF THERE ARE NO PEOPLE SPAWNING (RETURNING PASS)
    int totalNumOfPeople = 0;
    for (int i = 0; i < NUM_FLOORS; i++) {
        totalNumOfPeople += buildingState.floors[i].numPeople;
    }
    if (totalNumOfPeople == 0) {
        isAIPass = true;
    }
    
// PICKUP IF ELEVATORS ARE AT TARGET FLOORS ------ Pickup string output
    
    vector <int> elevForPickup;
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        int elevTargetFloor = buildingState.elevators[i].targetFloor;
        int elevCurrFloor = buildingState.elevators[i].currentFloor;
        
        if (elevTargetFloor == elevCurrFloor) {
            if (buildingState.floors[elevTargetFloor].numPeople != 0) {
                elevForPickup.push_back(i);
            }
        }
    }
    
    if (elevForPickup.size() != 0) {
        isAIPickupMove = true;
    }
    
// MOVE TO FLOOR MOVES ------------------
    
    // is a move to floor move if there are priority floors to pickup from else, pass
    if (priorityFloor.size() > 0) {
        char bestElevator = '0';
        
        // checking ea elevator's target floors
        for (int e = 0; e < NUM_ELEVATORS; e++) {
            _Elevator elevator = buildingState.elevators[e];
            for (int f = 0; f < priorityFloor.size() ; f++) {
                if (priorityFloor[f] > 0 && elevator.targetFloor == priorityFloor[f]) {
                    priorityFloor.erase(priorityFloor.begin());
                }
            }
        }
        
        //MOVE IF All ELEVATORS ARE IDLE (countServicing = 0), Move first elevator to priority floor
        if (countServicing == 0) {
            isAIMoveToFloor = true;
            bestElevator = listElevatorsAvail[0] + '0';
            AIMoveToFloor.at(1) = bestElevator;
        }
        
        //MOVE IF 2 ELEVATORS ARE SERVICING (countServicing = 2) ----,free elevator to priority floor sent
        if (countServicing == 2) {
            isAIMoveToFloor = true;
            bestElevator = listElevatorsAvail[0] + '0';
            AIMoveToFloor.at(1) = bestElevator;
        }
        
        //MOVE IF 1 ELEVATOR IS SERVICING (countServicing = 1) ----
        // checks if other elevators have same target floor
        if (countServicing == 1) {
            if (buildingState.elevators[listServicing[0]].targetFloor != priorityFloor[0]) {
                isAIMoveToFloor = true;
                
                int elevatorOneDifference = 0;
                int elevatorTwoDifference = 0;
                
                //checking difference between priority floor and current floor of first elevator
                _Elevator elevator1 = buildingState.elevators[listElevatorsAvail[0]];
                elevatorOneDifference = priorityFloor[0] - elevator1.currentFloor;
                elevatorOneDifference = abs(elevatorOneDifference);

                //checking difference between priority floor and current floor of second elevator
                _Elevator elevator2 = buildingState.elevators[listElevatorsAvail[1]];
                elevatorTwoDifference = priorityFloor[0] - elevator2.currentFloor;
                elevatorTwoDifference = abs(elevatorTwoDifference);

                //if first elevator is closer to target floor than the second, sending first elevator to priority floor
                if (elevatorOneDifference < elevatorTwoDifference) {
                    bestElevator = listElevatorsAvail[0] + '0';
                    AIMoveToFloor.at(1) = bestElevator;
                }

                //if second elevator is closer to target floor than the first, sending second elevator to priority floor
                else if (elevatorTwoDifference < elevatorOneDifference) {
                    bestElevator = listElevatorsAvail[1] + '0';
                    AIMoveToFloor.at(1) = bestElevator;
                }

                    //if first elevator is the same distance as the second
                else if (elevatorTwoDifference == elevatorOneDifference) {
                    bestElevator = listElevatorsAvail[0] + '0';
                    AIMoveToFloor.at(1) = bestElevator;
                }
            }
            else {
                isAIPass = true;
            }
        }
    }
    else {
        isAIPass = true;
    }
    
// FINAL OUTPUT
    if (isAIPass) {
        AIChosenMove = AIPassMove;
    }
    else if (isAIPickupMove) {
        AIPickupMove.at(1) = static_cast<char>(elevForPickup[0] + '0');
        elevForPickup.erase(elevForPickup.begin());
        AIChosenMove = AIPickupMove;
    }
    else if (isAIMoveToFloor) {
        priorityFloorChar = priorityFloor[0] + '0';
        AIMoveToFloor.at(3) = priorityFloorChar;
        AIChosenMove = AIMoveToFloor;
    }
    return AIChosenMove;
}
 
 
 
string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) {
    
    string pickupList = "";
    int maxAngerLevel = 0;
    int currentAngerLevel;
    int angerArray[floorToPickup.getNumPeople()];
    int arrayOfMaxAnger[floorToPickup.getNumPeople()];
    int countNumberOfMaxAnger = 0;
    int squaredSumUp = 0;
    int squaredSumDown = 0;
    
    //creates array of list of peoples angers
    for(int j = 0; j < floorToPickup.getNumPeople(); j++) {
            angerArray[j] = floorToPickup.getPersonByIndex(j).getAngerLevel();
        }
    //finds the max anger --> maxAngerLevel
    for(int i = 0; i < floorToPickup.getNumPeople(); i++) {
        currentAngerLevel = floorToPickup.getPersonByIndex(i).getAngerLevel();
        if(currentAngerLevel >= maxAngerLevel) {
            maxAngerLevel = currentAngerLevel;
        }
    }
    //number of people with max anger --> countNumbeOfMaxAnger
    //array of only people with max anger and which person they are --> arrayOfMaxAnger
    for(int a = 0; a < floorToPickup.getNumPeople(); a++) {
        if(floorToPickup.getPersonByIndex(a).getAngerLevel() == maxAngerLevel) {
            countNumberOfMaxAnger++;
            arrayOfMaxAnger[countNumberOfMaxAnger - 1] = a;
        }
    }
    
//    //when max anger == 0
//    int maxAngerZero = 0;
//    int maxAngerZeroArray[MAX_PEOPLE_PER_FLOOR] = {};
//
//    if (maxAngerLevel == 0) {
//        for(int a = 0; a < floorToPickup.getNumPeople(); a++) {
//            if(floorToPickup.getPersonByIndex(a).getAngerLevel() == 0) {
//                  maxAngerZeroArray[a] = maxAngerZero;
//                  ++maxAngerZero;
//            }
//
//        }
//        for (int i = 0; i < maxAngerZero; i++) {
//            char varChar = maxAngerZeroArray[i] + '0';
//            pickupList += varChar;
//          }
//      }

    //if there is more than 1 person with max anger, sum of angers squared of people gonig up, sum of angers of people going down
    if(countNumberOfMaxAnger > 1) {
        // anger multipliers
           for (int b = 0; b < floorToPickup.getNumPeople(); b++) {
               //if it has a down request
               if(floorToPickup.getPersonByIndex(b).getTargetFloor() < floorToPickup.getPersonByIndex(b).getCurrentFloor()) {
                   squaredSumDown += pow(floorToPickup.getPersonByIndex(b).getAngerLevel(), 2);
               }
               if(floorToPickup.getPersonByIndex(b).getTargetFloor() > floorToPickup.getPersonByIndex(b).getCurrentFloor()) {
                   squaredSumUp += pow(floorToPickup.getPersonByIndex(b).getAngerLevel(), 2);
               }
           }
        //picks up all down requests
        if(squaredSumDown > squaredSumUp) {
            for(int c = 0; c < floorToPickup.getNumPeople(); c++) {
                if(floorToPickup.getPersonByIndex(c).getTargetFloor() < floorToPickup.getPersonByIndex(c).getCurrentFloor()) {
                    char varChar = c + '0';
                    pickupList += varChar;
                }
            }
        //picks up all up requests
        } else {
            for(int d = 0; d < floorToPickup.getNumPeople(); d++) {
                if(floorToPickup.getPersonByIndex(d).getTargetFloor() > floorToPickup.getPersonByIndex(d).getCurrentFloor()) {
                    char varChar = d + '0';
                    pickupList += varChar;
                }
            }
        }
    //if there is only 1 person with max anger we take the people going the same direction as that of the max person
    } else {
        for(int e = 0; e < floorToPickup.getNumPeople(); e++) {
            if(floorToPickup.getPersonByIndex(e).getAngerLevel() == maxAngerLevel) {
                //if has down request
                if(floorToPickup.getPersonByIndex(e).getTargetFloor() < floorToPickup.getPersonByIndex(e).getCurrentFloor()) {
                    for(int f = 0; f < floorToPickup.getNumPeople(); f++) {
                        if(floorToPickup.getPersonByIndex(f).getTargetFloor() < floorToPickup.getPersonByIndex(f).getCurrentFloor()) {
                            char varChar = f + '0';
                            pickupList += varChar;
                        }
                    }
                //if has up request
                } else {
                    for(int g = 0; g < floorToPickup.getNumPeople(); g++) {
                        if(floorToPickup.getPersonByIndex(g).getTargetFloor() > floorToPickup.getPersonByIndex(g).getCurrentFloor()) {
                            char varChar = g + '0';
                            pickupList += varChar;
                        }
                    }
                }
            }
        }
    }
    
    return pickupList;
}
