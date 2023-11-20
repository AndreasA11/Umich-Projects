/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <random>
#include <sstream>
#include "Game.h"
#include "AI.h"
#include "Utility.h"
using namespace std;
 
// Stub for playGame for Core, which plays random games
// You *must* revise this function according to the RME and spec
void Game::playGame(bool isAIModeIn, ifstream& gameFile) {
    std::mt19937 gen(1);
        std::uniform_int_distribution<> floorDist(0, 9);
        std::uniform_int_distribution<> angerDist(0, 3);
     
        if (!gameFile.is_open()) {
            exit(EXIT_FAILURE);
        }
        
        isAIMode = isAIModeIn;
        printGameStartPrompt();
        initGame(gameFile);
     
        string loadFile;
        while (gameFile >> loadFile) {
            Person p1(loadFile);
                while(building.getTime() <= p1.getTurn()){
                    building.prettyPrintBuilding(cout);
                    satisfactionIndex.printSatisfaction(cout, false);
                    checkForGameEnd();
                    Move nextMove = getMove();
                    update(nextMove);
                }
            building.spawnPerson(p1);
            
        }
        
        while (true) {
            building.prettyPrintBuilding(cout);
            satisfactionIndex.printSatisfaction(cout, false);
            checkForGameEnd();
     
            Move nextMove = getMove();
            update(nextMove);
     
        }
    }


// Stub for isValidPickupList for Core
// You *must* revise this function according to the RME and spec
bool Game::isValidPickupList(const string& pickupList, const int pickupFloorNum) const {
    
    // Check for length of pickupList
    if (pickupList.size() > ELEVATOR_CAPACITY) {
        return false;
    }
    // Converting string to char then into int array
    int i = 0;
    int j = 0;
    int pickup_array[pickupList.size()];
    
    for (i = 0; i < pickupList.size(); i++) {
        int inNum = static_cast<char>(pickupList.at(i)) - '0';
        pickup_array[i] = inNum;
    }
    
    // Checking for no duplicates
    for (i = 0; i < pickupList.size(); i++) {
        for (j = i + 1; j < pickupList.size(); j++) {
            if (pickup_array[i] == pickup_array[j]) {
                return false;
            }
        }
    }
    
    // Checking no negative digits & searching for maximum index val
    int maxVal = 0;
    for (i = 0; i < pickupList.size(); i++) {
        if (pickup_array[i] < 0) {
            return false;
        }
        if (i == 0) {
            maxVal = pickup_array[0];
        }
        else {
            if (pickup_array[i] > maxVal) {
                maxVal = pickup_array[i];
            }
        }
    }
    
    // checking maxVal doesnt exceed number of people on the appointed floor
    if (maxVal >= building.getFloorByFloorNum(pickupFloorNum).getNumPeople()) {
        return false;
    }
    
    // checking direction
    int initTargetFloor =
    building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickup_array[0]).getTargetFloor();
    int initDirection = initTargetFloor - pickupFloorNum;
    int personDirection = 0;
    
    if (initDirection > 0) {
        for (i = 0; i < pickupList.size(); i++) {
            int targetFloor = building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickup_array[i]).getTargetFloor();
            personDirection = targetFloor - pickupFloorNum;
            if (personDirection < 0) {
                return false;
            }
        }
    }
    else if (initDirection < 0) {
        for (i = 0; i < pickupList.size(); i++) {
            int targetFloor = building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickup_array[i]).getTargetFloor();
            personDirection = targetFloor - pickupFloorNum;
            if (personDirection > 0) {
                return false;
            }
        }
    }
    
    return true;
}


//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

bool Game::performMove(Move& move) const
{
    Elevator elevators[NUM_ELEVATORS];

    for (int i = 0; i < NUM_ELEVATORS; ++i)
    {
        elevators[i] = building.getElevatorById(i);
    }

    if (move.isValidMove(elevators) && move.isPickupMove())
    {

        Elevator taggedElevator = building.getElevatorById(move.getElevatorId());
        Floor taggedFloor = building.getFloorByFloorNum(taggedElevator.getCurrentFloor());

        if (taggedFloor.getNumPeople() > 0)
        {
            getPeopleToPickup(move);
            return true;
        }

        return false;
    }
    else if (move.isSaveMove())
    {
        performSave();
    }
    else if (move.isQuitMove())
    {
        performQuit();
    }
    else if (!move.isValidMove(elevators))
    {
        return false;
    }

    return true;
}

void Game::printWelcomeMenu() const
{
    cout << "########################################" << endl;
    cout << "# Welcome to EECS 183 Elevator Escape! #" << endl;
    cout << "########################################" << endl
        << endl;
}

void Game::printIntroMenu() const
{
    cout << "[0] Run Tests" << endl;
    cout << "[1] Load saved game" << endl;
    cout << "[2] Start new game" << endl;
    cout << "Choice: ";
}

void Game::printAIMenu() const {
    cout << "[1] Play as human" << endl;
    cout << "[2] Watch AI play" << endl;
    cout << "Choice: ";
}

void Game::printOptions() const
{
    cout << "########################################" << endl;
    cout << "#         Enter service move:          #" << endl;
    cout << "#     'e' elevatorId 'f' floorNum      #" << endl;
    cout << "#            Or pickup move:           #" << endl;
    cout << "#          'e' elevatorId 'p'          #" << endl;
    cout << "########################################" << endl;
}

void Game::printGameStartPrompt() const
{
    cout << endl;
    cout << "########################################" << endl;
    cout << "#                 Enter:               #" << endl;
    cout << "#               Q to Quit              #" << endl;
    cout << "#               S to Save              #" << endl;
    cout << "#      At any time after this prompt   #" << endl;
    cout << "########################################" << endl;
    cout << endl;
    cout << "Press enter to continue....";

    string trash;
    getline(cin, trash);
    cout << endl;
}

IntroChoice Game::getIntroChoice() const {

    if (IS_AI_OVERRIDE) {
        return IntroChoice::New;
    }

    int choice = -1;

    while ((choice < 0) || (choice > 2))
    {
        printIntroMenu();
        string s_choice;
        getline(cin, s_choice);
        choice = stoi(s_choice);

        if ((choice < 0) || (choice > 2))
        {
            cout << endl
                << "Invalid menu choice!" << endl
                << endl;
        }
    }

    cout << endl;

    return static_cast<IntroChoice>(choice);
}

AIChoice Game::getAIChoice() const {
    if (IS_AI_OVERRIDE) {
        return AIChoice::AI;
    }

    int choice = 0;
    printAIMenu();
    string s_choice;
    getline(cin, s_choice);
    choice = stoi(s_choice);
    while (choice != 1 && choice != 2) {
        cout << endl << "Invalid menu choice!" << endl << endl;
        getline(cin, s_choice);
        choice = stoi(s_choice);
    }

    cout << endl;

    return static_cast<AIChoice>(choice);
}

void Game::printSatisfactionIndex() const
{
    cout << endl
        << endl;
    cout << "Your hotel's current satisfaction index is: " << satisfactionIndex;
    cout << endl
        << endl;
}

void Game::getPeopleToPickup(Move& move) const
{
    int currentFloorNum = building.getElevatorById(move.getElevatorId()).getCurrentFloor();
    Floor currentFloor = building.getFloorByFloorNum(currentFloorNum);

    if (currentFloor.getNumPeople() == 1)
    {
        move.setPeopleToPickup("0", currentFloorNum, currentFloor);
        return;
    }

    string peopleIndices = "";
    bool isValidPickup = false;

    while (!isValidPickup)
    {

        currentFloor.printFloorPickupMenu(cout);
        cout << endl;
        cout << "Choices: ";
        getline(cin, peopleIndices);
        cout << "\n";

        if (isAIMode) {
            Elevator e = building.getElevatorById(move.getElevatorId());
            Floor f = building.getFloorByFloorNum(e.getCurrentFloor());
            peopleIndices = getAIPickupList(move, building.getBuildingState(), f);
            cout << "AI OVERRIDE: " << peopleIndices << endl;
        }

        isValidPickup = isValidPickupList(peopleIndices, currentFloorNum);

        if (!isValidPickup)
        {
            cout << "Invalid list of people chosen!" << endl;
            checkForGameEnd();
        }
    }

    move.setPeopleToPickup(peopleIndices, currentFloorNum, currentFloor);
}

Move Game::getMove() const
{
    Move moveObj;
    string moveString = "";
    bool isValid = false;
    GameChoice choiceCapture = GameChoice::Invalid;

    do
    {
        cout << "Enter move: ";

        getline(cin, moveString);
        cout << "\n";

        if (isAIMode) {
            moveString = getAIMoveString(building.getBuildingState());
            cout << "AI OVERRIDE: " << moveString << endl;
        }
        moveObj = Move(moveString);
        choiceCapture = static_cast<GameChoice>(moveString[0]);

        switch (choiceCapture)
        {
        case GameChoice::Quit:
            performQuit();
            break;
        case GameChoice::Save:
            isValid = performSave();
            break;
        case GameChoice::Pass:
        case GameChoice::Move:
            isValid = performMove(moveObj);
            break;
        default:
            isValid = false;
            break;
        }

        if (!isValid)
        {
            cout << endl
                << "Invalid move!" << endl
                << endl;
            checkForGameEnd();
        }

    } while (!isValid);

    return moveObj;
}

void Game::performQuit() const
{
    QuitChoice quitChoice = static_cast<QuitChoice>(getExitChoice());
    switch (quitChoice)
    {
    case QuitChoice::Quit:
        endGame();
        break;
    case QuitChoice::Stay:
        return;
        break;
    }
}

bool Game::performSave() const
{
    ofstream saveFile(LOAD_FILENAME);
    if (!saveFile.is_open())
    {
        cout << "Could not open " << LOAD_FILENAME << endl;
        return false;
    }
    return saveGame(saveFile);
}

void Game::initGame(ifstream& loadFile)
{
    cout << endl
        << "Loading game..." << endl;

    loadFile >> satisfactionIndex;

    int tempTime;
    loadFile >> tempTime;

    building.setTime(tempTime);

    string elvState;
    for (int i = 0; i < NUM_ELEVATORS; i++)
    {
        loadFile >> elvState;
        building.setElevator(elvState, i);
    }

    cout << "Loaded!" << endl
        << endl;
}

void Game::printExitMenu() const
{
    cout << endl;
    cout << "Are you sure you want to quit?" << endl;
    cout << "[1] Yes, I'm sure!" << endl;
    cout << "[2] No, keep playing!" << endl;
    cout << "Choice: ";
}

int Game::getExitChoice() const
{
    int exitChoice = 0;

    while ((exitChoice < 1) || (exitChoice > 2))
    {
        printExitMenu();

        string choice = "";
        getline(cin, choice);
        exitChoice = stoi(choice);

        if ((exitChoice < 1) || (exitChoice > 2))
        {
            cout << endl
                << "Invalid menu choice!" << endl
                << endl;
        }
    }
    cout << endl;

    return exitChoice;
}

void Game::endGame() const
{
    cout << endl
        << "Goodbye!" << endl;
    satisfactionIndex.save();
    exit(0);
}

void Game::printSuccessEnding() const
{
    cout << endl
        << endl;
    cout << "Time is up! Your final score is: " << endl;
    satisfactionIndex.printSatisfaction(cout);
}

void Game::printFailureEnding() const
{
    cout << endl
        << endl;
    cout << "Uh oh! Your hotel has gone out of business!" << endl;
    cout << "Better luck next time!" << endl
        << endl;
    cout << "Your final achievement:" << endl
        << endl;
    satisfactionIndex.printSatisfaction(cout);
}

void Game::checkForGameEnd() const
{
    if (building.getTime() >= MAX_TURNS)
    {
        printSuccessEnding();
        endGame();
    }
    else if (satisfactionIndex.getSatisfaction() < 0)
    {
        printFailureEnding();
        endGame();
    }
}

void Game::update(const Move& m)
{
    if (m.isPickupMove())
    {
        satisfactionIndex.updateSumDirectionRequest(m, building);
    }
    satisfactionIndex.updateSumExploded(building.tick(m));
    satisfactionIndex.updateTimeReached(building);
    if (building.getTime() % 2)
    {
        satisfactionIndex.updateSumIdle(building);
    }
}

// Stub for saveGame for project
// You will *not* implement this function for the project
bool Game::saveGame(ofstream& saveFile) const {
    return true;
}
