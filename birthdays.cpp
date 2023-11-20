/**
 * birthdays.cpp
 * Project UID: 59fc568b7f83f8c109ae360f448f7f821ba0a71
 * 
 * Andreas Andrade
 * aadredre
 *
 * EECS 183: Project 2
 *
 * <#description#>
 */

#include <cmath>
#include <iostream>
#include <string>

using namespace std;


/**
 * REQUIRES: nothing
 * MODIFIES: cout
 * EFFECTS:  Prints out the initial heading for the program
 */
void printHeading();


/**
 * REQUIRES: nothing
 * MODIFIES: cout
 * EFFECTS:  Prints out the final greeting for the program
 */
void printCloser();


/**
 * REQUIRES: nothing
 * MODIFIES: cout 
 * EFFECTS:  Prints the menu text. Does not read from cin.
 */
void printMenu();

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: nothing
 * MODIFIES: cout, cin
 * EFFECTS:  1. Prints the menu
 *           2. Reads the input from the user
 *           3. Checks to make sure the input is within range for the menu
 *              If not prints "Invalid menu choice"
 *           4. Continues to print the menu and read an input until 
 *              a valid one is entered
 *           5. Returns the user's choice of menu options
 * 
 *           This function must call printMenu().
 */
int getMenuChoice();

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: month, day, year represent a valid date
 * MODIFIES: nothing
 * EFFECTS:  Returns true if the date is in the limits
 *           of the Gregorian calendar otherwise returns false
 *           See the spec for definition of "limits of the Gregorian calendar"
 */
bool isGregorianDate(int month, int day, int year);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: year is a Gregorian year
 * MODIFIES: nothing
 * EFFECTS:  returns true if the year is a leap year
 *           otherwise returns false.
 *           See the spec for definition of a leap year.
 */
bool isLeapYear(int year);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: month, day, year may represent a date
 * MODIFIES: nothing
 * EFFECTS:  returns true if the date is valid
 *           otherwise returns false
 *           See the spec for definition of "valid"
 */
bool isValidDate(int month, int day, int year);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: month, day, year is a valid date
 *           i.e., the date passed to this function has already passed
 *               isValidDate()
 * MODIFIES: nothing
 * EFFECTS:  returns the value f that Zeller's formula calculates
 */
int determineDay(int month, int day, int year);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: day is a value of f output by Zeller's formula
*            (0 represents Saturday, 1 Sunday, 2 Monday, 3 Tuesday, etc)
 * MODIFIES: cout
 * EFFECTS:  prints the day of the week corresponding to day, suchas
 *           "Sunday", "Monday", ..., "Saturday"
 */
void printDayOfBirth(int day);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: nothing
 * MODIFIES: cout, cin
 * EFFECTS:  Asks for the month / day / year of the user's birthday.
 *           If the date is valid, it will print the day
 *           of the week you were born on
 *           Otherwise, it will print "Invalid date" prompt.
 */
void determineDayOfBirth();

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: nothing
 * MODIFIES: cin, cout
 * EFFECTS:  Asks for a Gregorian year and prints the
 *           10 leap years after (not including) the year entered.
 *           If the year is invalid, it prints nothing.
 *
 *           This function must call isLeapYear().
 */
void print10LeapYears();

/* 
 * EFFECTS: Main driver for the Birthdays program. See the
 *          "Putting it Together" section of the spec for what
 *          this function needs to accomplish.
 */
void birthdays() {    
    printHeading();
    int menuChoice = getMenuChoice();
    while(menuChoice != 3) {
        if(menuChoice == 1) {
            
            determineDayOfBirth();
            menuChoice = getMenuChoice();
        }
        if(menuChoice == 2) {
            
            print10LeapYears();
            menuChoice = getMenuChoice();
        }
    }
    if(menuChoice == 3) {
        printCloser();
    }
        
}


void printHeading() {
    cout << "*******************************" << endl
         << "      Birthday Calculator      " << endl
         << "*******************************" << endl << endl;
}


void printCloser() {
    cout << endl;
    cout << "****************************************************" << endl
         << "      Thanks for using the Birthday Calculator      " << endl
         << "****************************************************" << endl
         << endl;
}


void printMenu() {
    cout << endl;
    cout << "Menu Options" << endl
         << "------------" << endl;
    cout << "1) Determine day of birth" << endl;
    cout << "2) Print the next 10 leap years" << endl;
    cout << "3) Finished" << endl << endl;
    
    cout << "Choice --> ";
}

int getMenuChoice() {
    int menuChoice;
    printMenu();
    cin >> menuChoice;
    while(menuChoice != 1 && menuChoice != 2 && menuChoice != 3) {
        cout << endl;
        cout << "Invalid menu choice ";
        cout << endl;
        printMenu();
        cin >> menuChoice;
    }
    
    return menuChoice;
}

bool isGregorianDate(int month, int day, int year) {
    bool isGregorianDate;
    //it is a Georgian date if the date is 9/14/1752 or later
    //checks in following order:
    //checks if year is before 1752
    //if month is before 9(september) and year is 1752
    //if day is before 14 and month is before 9 and year is 1752
    if(year < 1752) {
        isGregorianDate = false;
    } else if(year == 1752 && month < 9) {
        isGregorianDate = false;
    }  else if(year == 1752 && month == 9 && day < 14) {
        isGregorianDate = false;
    } else {
        isGregorianDate = true;
    }
    return isGregorianDate;
}

bool isLeapYear(int year) {
    //checks in following order:
    //if year is evenly divisible by 400 then it is a leap year
    //if year is evenly divisible by 100 then it is not leap year
    //if year is evenly divisible by 4 then it is a leap year
    bool isLeapYear;
    if(year % 400 == 0) {
        isLeapYear = true;
    } else if(year % 100 == 0) {
        isLeapYear = false;
    } else if(year % 4 == 0) {
        isLeapYear = true;
    } else {
        isLeapYear = false;
    }
    return isLeapYear;
}


bool isValidDate(int month, int day, int year) {
    bool isValidDate = true;
    int invalidDay = 0;
    //checking Feb (leap year and not leap year)
    if(isGregorianDate(month, day, year)) {
        if(month > 0 && month < 13) {
            if(month == 2) {
                if(isLeapYear(year)) {
                    if(day > 29 || day <= invalidDay) {
                        isValidDate = false;
                    }
                }else if(!isLeapYear(year)) {
                    if(day > 28 || day <= invalidDay) {
                        isValidDate = false;
                    }
                }
                //these numbers are the months with 31 days
            } else if(month == 1 || month == 3 || month == 5 || month == 7
                      || month == 8 || month == 10 || month == 12) {
                if(day > 31 || day <= invalidDay) {
                    isValidDate = false;
                }
                //these numbers are the months with 30 days
            } else if(month == 4 || month == 6 || month == 9 || month == 11) {
                if(day > 30 || day <= invalidDay) {
                    isValidDate = false;
                }
            }
        } else {
            isValidDate = false;
        }
    } else {
        isValidDate = false;
    }
    return isValidDate;
}


int determineDay(int month, int day, int year) {
    int dayOfWeek;
    int M = month;
    if(M == 1) {
        //adjusted month for Jan
        M = 13;
        year -= 1;
    } else if(month == 2) {
        //adjusted month for Feb
        M = 14;
        year -= 1;
    }
    int D = day;
    //this 100 finds the last two digets of the year(if 2064 --> 64)
    int Y = year % 100;
    //this 100 finds the first two digits of the year(if 2064 --> 20)
    int C = year / 100;
    dayOfWeek = (D + ((13 * (M + 1)) / 5) + Y + (Y / 4) + (C / 4) + 5 * C) % 7;
    return dayOfWeek;
}


void printDayOfBirth(int day) {
    if(day == 0) {
        cout << "Saturday";
    } else if(day == 1) {
        cout << "Sunday";
    } else if(day == 2) {
        cout << "Monday";
    } else if(day == 3) {
        cout << "Tuesday";
    } else if(day == 4) {
        cout << "Wednesday";
    } else if(day == 5) {
        cout << "Thursday";
    } else {
        cout << "Friday";
        }
    
}


void determineDayOfBirth() {
    cout << "Enter your date of birth " << endl;
    cout << "format: month / day / year --> ";
    int month;
    int day;
    int year;
    string garbageCan;
    cin >> month;
    cin >> garbageCan;
    cin >> day;
    cin >> garbageCan;
    cin >> year;
    cout << endl;
    
    if(!(isValidDate(month, day, year))) {
        cout << "Invalid date" << endl;
    } else if (isValidDate(month, day, year)) {
        cout << "You were born on a: ";
        printDayOfBirth(determineDay(month, day, year));
        cout << endl << endl;
        cout << "Have a great birthday!!!" << endl << endl;
    }
}

void print10LeapYears() {
    cout << "Enter year --> ";
    int leapYear;
    int year;
    int loop = 10;
    cin >> year;
    cout << endl;
    if(year >= 1752) {
        if((isLeapYear(year))) {
            leapYear = year + 4;
            for(int i = 0; i < loop; i++) {
                cout << "Leap year is " << leapYear << endl;
                leapYear += 4;
            }
            cout << endl;
        } else if((isLeapYear(year + 1))) {
                leapYear = year + 1;
                for(int i = 0; i < loop; i++) {
                    cout << "Leap year is " << leapYear << endl;
                    leapYear += 4;
                }
            cout << endl;
        } else if((isLeapYear(year + 2))) {
                leapYear = year + 2;
                for(int i = 0; i < loop; i++) {
                    cout << "Leap year is " << leapYear << endl;
                    leapYear += 4;
                }
            cout << endl;
        } else {
            leapYear = year + 3;
            for(int i = 0; i < loop; i++) {
                cout << "Leap year is " << leapYear << endl;
                leapYear += 4;
                    }
            cout << endl;
                }
            }
        }
    

