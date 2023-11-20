/**
 * focaccia.cpp
 *
 * Andreas Andrade
 * aadredre
 *
 * EECS 183: Project 1
 * Fall 2022
 *
 * Project UID: d435ced1b1ee1e06372665b53322301c67d2d4a0
 *
 *  finds out the list of ingredients and price for a certain number of focaccia
 *  bread based on the number of people you need to serve
 */

#include <iostream>
#include <cmath>
# include <string>

using namespace std;

/**
 * Returns the singular or plural form of a word, based on number
 *
 * Requires: singular is the singular form of the word.
 *           plural is the plural form of the word.
 *           number determines how many things there are; must be >= 0.
 * Modifies: Nothing.
 * Effects:  Returns return the singular form of the word if number == 1.
 *           Otherwise, returns the plural form.
 * Examples:
 *           // prints "bag"
 *           cout << pluralize("bag", "bags", 1);
 *
 *           // prints "pounds"
 *           string temp = pluralize("pound", "pounds", 3);
 *           cout << temp;
 */
string pluralize(string singular, string plural, int number);

//number of loaves of focaccia needed
int focacciaNeeded;

/**
 * Returns the number of people needed to be served
 *
 * Requires: numberOfPeople which is an int that takes user input
 * asking how many people need to be served
 * Modifies: Nothing.
 * Effects:  Returns the number of people needed to be served
 * Examples:
 *
 *  //prints "12"
 *  //user input is 12
 *  cin >> numPeople;
 *  cout << getNumOfPeople(numPeople);
 *   
 */
int getNumOfPeople(int numberOfPeople) {
    return numberOfPeople;
}

/**
 * Returns the loaves of focaccia needed to be served
 *
 * Requires: focacciaNeeded which is an int that is the number
 * of loaves needed
 * Modifies: Nothing.
 * Effects:  Returns the amount of focaccia needed to be served
 * Examples:
 *
 *  //prints "12"
 *  //focacciaNeeded is 12
 *  cout << getLoavesOfFocaccia(focacciaNeeded);
 *
 */
//returns the # of loaves of foccocia needed
int getLoavesOfFocaccia(int focacciaNeeded) {
    return focacciaNeeded;
}

/**
 * calculates and returns the bags of flour needed
 *
 * Requires: N/A
 * Modifies: Nothing.
 * Effects:  calculates and returns the bags of flour needed
 * Examples:
 * //prints 3
 * //In this situation after calcualtions totalBags is 3
 * cout << amountOfFlour();
 *
 */
//calculates and returns the amount of bags of flour needed
int amountOfFlour() {
    const int CUP_PER_LOAF = 5;
    const int POUNDS_PER_BAG = 20;
    int totalFlour = getLoavesOfFocaccia(focacciaNeeded) * CUP_PER_LOAF;
    int totalBags = ceil(static_cast<double>(totalFlour) / POUNDS_PER_BAG);
    
    return totalBags;
}

/**
 * calculates and returns the packages of yeast needed
 *
 * Requires: N/A
 * Modifies: Nothing.
 * Effects:  calculates and returns the packages of yeast needed
 * Examples:
 * //prints 3
 * //In this situation after calcualtions totalPackages is 3
 * cout << amountOfFlour();
 *
 */
//calculates and returns the amount of packages of yeast needed
int amountOfYeast() {
    const double YEAST_TSP_PER_LOAF = 1.75;
    const double TSP_PER_PACKAGE = 2.25;
    double totalYeast = getLoavesOfFocaccia(focacciaNeeded) * YEAST_TSP_PER_LOAF;
    int totalPackages = ceil(totalYeast / TSP_PER_PACKAGE);
    
    return totalPackages;
}

/**
 * calculates and returns the canisters of salt needed
 *
 * Requires: N/A
 * Modifies: Nothing.
 * Effects:  calculates and returns the canisters of salt needed
 * Examples:
 * //prints 3
 * //In this situation after calcualtions totalCanisters is 3
 * cout << amountOfFlour();
 *
 */

//calculates and returns the amount of canisters of salt needed
int amountOfSalt() {
    const double SALT_TSP_PER_LOAF = 1.875;
    const int GM_PER_CANISTER = 30;
    const int GM_PER_TSP = 5;
    double totalSalt = getLoavesOfFocaccia(focacciaNeeded) * SALT_TSP_PER_LOAF;
    totalSalt *= GM_PER_TSP;
    int totalCanisters = ceil(static_cast<double>(totalSalt) / GM_PER_CANISTER);
    
    return totalCanisters;
}

/**
 * calculates and returns the bottles of olive oil needed
 *
 * Requires: N/A
 * Modifies: Nothing.
 * Effects:  calculates and returns the bottles of olive oil needed
 * Examples:
 * //prints 3
 * //In this situation after calcualtions total Bottles is 3
 * cout << amountOfFlour();
 *
 */

//calculates and returns the amount of bottles of oil needed
int amountOfOil() {
    const int TBSP_PER_LOAF = 2;
    const double ML_PER_TBSP = 14.8;
    const int ML_PER_BOTTLE = 500;
    int totalOil = getLoavesOfFocaccia(focacciaNeeded) * TBSP_PER_LOAF;
    totalOil *= ML_PER_TBSP;
    int totalBottles = ceil(static_cast<double>(totalOil) / ML_PER_BOTTLE);
    
    
    return totalBottles;
}

/**
 * prints  the list of ingredients
 *
 * Requires: N/A
 * Modifies: Nothing.
 * Effects:  prints the list of ingredients
 * //assumes we need 6 bags of flour, 18 packages of yeast
 * //8 canisters of salt, 2 bottkes of olive oil
 * //prints:
 * //6 bags of flour
 * //18 packages of yeast
 * //8 canisters of salt
 * //2 bottles of olive oil
 *
 *cout << amountOfIngredients;
 */

//calculates and prints how much total ingredients needed
int amountOfIngredients() {
    
    cout << amountOfFlour() << " "
         << pluralize("bag", "bags", amountOfFlour())<< " of flour \n";
    cout << amountOfYeast() << " "
         << pluralize("package", "packages", amountOfYeast()) << " of yeast \n";
    cout << amountOfSalt() << " "
         << pluralize("canister", "canisters", amountOfSalt()) << " of salt \n";
    cout << amountOfOil() << " "
         << pluralize("bottle", "bottles", amountOfOil()) << " of olive oil \n";
    cout << endl;
    
    return 0;
}

/**
 * calculates cost and returns it
 *
 * Requires: N/A
 * Modifies: Nothing.
 * Effects:  calculates cost and rreturns it
 * //assumes we need 6 bags of flour, 18 packages of yeast
 * //8 canisters of salt, 2 bottkes of olive oil
 * //prints: 40.04
 *
 * cout << getCost;
 */
//calculates and returns total cost of ingredients
double getCost() {
    const double COST_PER_BAG = 2.69;
    const double COST_PER_PACKAGE = 0.4;
    const double COST_PER_CANISTER = 0.49;
    const double COST_PER_BOTTLE = 6.39;
    double costOfFlour = amountOfFlour() * COST_PER_BAG;
    double costOfYeast = amountOfYeast() * COST_PER_PACKAGE;
    double costOfSalt = amountOfSalt() * COST_PER_CANISTER;
    double costOfOil = amountOfOil() * COST_PER_BOTTLE;
    double totalCost = costOfFlour + costOfYeast + costOfSalt + costOfOil;
    
    return totalCost;
}

//main fucntion
//prints out all of the prompts and information to the user(formatting section)
int main(int argc, const char * argv[]) {
    int numPeople;
    
    cout << "How many people do you need to serve? ";
    cin >> numPeople;
    cout << endl << endl;
    
    
    focacciaNeeded = ceil(static_cast<double>(getNumOfPeople(numPeople)) / 4);
    
    cout << "You need to make: " << focacciaNeeded
         << " " << pluralize("loaf", "loaves", focacciaNeeded) << " of focaccia \n";
    cout << endl;
    
    cout << "Shopping List for Focaccia Bread \n ";
    cout << "-------------------------------- \n ";
    
    amountOfIngredients();
    
    cout << "Total expected cost of ingredients: $" << getCost() << "\n";
    cout << endl;
    cout << "Have a great party! \n";
    return 0;
}

//discription above
//makes word pluralized or singular based on # of items needed
string pluralize(string singular, string plural, int number) {
    if (number == 1) {
        return singular;
    }
    return plural;
}

