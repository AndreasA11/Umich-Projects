/**
 * ohhi.cpp
 * Project UID 5557cbe19b6ff413629a3743c503275413233136
 *
 * EECS 183
 * Project 3: 0h h1
 *
 * Andreas Andrade
 * aadredre
 *
 * code for functions in ohhi
 * counter, checker, and solver
 */

#include <iostream>
#include <cctype>
#include "utility.h"
#include "ohhi.h"

/**
 * --------------------------------------------------------
 * ---------- UTILITY FUNCTIONS ---------------------------
 * --------------------------------------------------------
 */
const int DIVIDE_BY_TWO = 2;


int count_unknown_squares(const int board[MAX_SIZE][MAX_SIZE], int size) {
    int unkownCounter = 0;
    //loops through and counts how many unkonws there are, counter starts at 0
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            if(board[row][col] == UNKNOWN) {
                unkownCounter++;
            }
        }
    }
    return unkownCounter;
}


/**
 * --------------------------------------------------------
 * --------- VALIDITY CHECKING FUNCTIONS ------------------
 * --------------------------------------------------------
 */

bool row_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int row,
                                int color) {
    bool hasNoThreeOfColorRow = true;
    int sizeLim = size - 2;
        for(int col = 0; col < sizeLim; col++) {
            //cannot have three in a row if size is 2
            if(size == 2) {
                hasNoThreeOfColorRow = true;
                return hasNoThreeOfColorRow;
            } else {
            if(color == RED) {
                if(board[row][col] == RED) {
                    //checking if there are three in a row for red
                    if(board[row][col] == board[row][col + 1] &&
                       board[row][col] == board[row][col + 2]) {
                        hasNoThreeOfColorRow = false;
                    }
                }
            } else if (color == BLUE) {
                if (board[row][col] == BLUE) {
                    //checking if there are three in a row for blue
                    if(board[row][col] == board[row][col + 1] &&
                       board[row][col] == board[row][col + 2]) {
                        hasNoThreeOfColorRow = false;
                    }
                }

            } else {
                if(board[row][col] == UNKNOWN) {
                    //checking if there are three in a row for unkown
                    if(board[row][col] == board[row][col + 1] &&
                       board[row][col] == board[row][col + 2]) {
                        hasNoThreeOfColorRow = false;
                    }
                }
            }
        }
            
    }
    return hasNoThreeOfColorRow;
}

bool col_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int col,
                                int color) {
    bool hasNoThreeOfColorCol = true;
        for(int row = 0; row < size - 2; row++) {
            //cannot have three in a column if size is 2
            if(size == 2) {
                hasNoThreeOfColorCol = true;
                return hasNoThreeOfColorCol;
            } else {
            if(color == RED) {
                if(board[row][col] == RED) {
                    //checking three in a column for red
                    if(board[row][col] == board[row + 1][col] &&
                       board[row][col] == board[row + 2][col]) {
                        hasNoThreeOfColorCol = false;
                    }
                }
            } else if (color == BLUE) {
                if (board[row][col] == BLUE) {
                    //checking three in a column for blue
                    if(board[row][col] == board[row + 1][col] &&
                       board[row][col] == board[row + 2][col]) {
                        hasNoThreeOfColorCol = false;
                    }
                }

            } else {
                if(board[row][col] == UNKNOWN) {
                    //checking three in  a column for unknown
                    if(board[row][col] == board[row + 1][col] &&
                       board[row][col] == board[row + 2][col]) {
                        hasNoThreeOfColorCol = false;
                    }
                }
            }

        }
    }
    return hasNoThreeOfColorCol;
}

bool board_has_no_threes(const int board[MAX_SIZE][MAX_SIZE], int size) {
    bool noThrees = true;
    for(int row = 0; row < size; row++) {
        int color = RED;
        //if there are three reds in a row return false
        if(!(row_has_no_threes_of_color(board, size, row, color))) {
            noThrees = false;
            return noThrees;
        }
        color = BLUE;
        //if there are three blues in a row return false
        if(!(row_has_no_threes_of_color(board, size, row, color))) {
            noThrees = false;
            return noThrees;
        }
        for(int col = 0; col < size; col++) {
            color = RED;
            //if there are three reds in a column return false
            if(!(col_has_no_threes_of_color(board, size, col, color))) {
                noThrees = false;
                return noThrees;
            }
            color = BLUE;
            //if there are three blues in a column return false
            if(!(col_has_no_threes_of_color(board, size, col, color))) {
                noThrees = false;
                return noThrees;
            }
        }
    }
    return noThrees;
}

bool rows_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int row1,
                        int row2) {
    bool differentRows = false;
    for(int col = 0; col < size; col++) {
        //if either row has an unkown then return true
        if(board[row1][col] == UNKNOWN || board[row2][col] == UNKNOWN) {
            differentRows = true;
    //if the two rows have a different value then they are different, return true
        } else if (board[row1][col] != board[row2][col]) {
            differentRows = true;
        }
    }
    return differentRows;
}

bool cols_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int col1,
                        int col2) {
    bool differentCols = false;
    for(int row = 0; row < size; row++) {
        //if either colum has an unkown then return true
        if(board[row][col1] == UNKNOWN || board[row][col2] == UNKNOWN) {
            differentCols = true;
        //if the two columns have a different value then they are differnet, return true
        } else if (board[row][col1] != board[row][col2]) {
            differentCols = true;
        }
    }
    return differentCols;
}

bool board_has_no_duplicates(const int board[MAX_SIZE][MAX_SIZE], int size) {
    bool noDuplicates = true;
    for(int row = 0; row < size; row++) {
        for(int row2 = 0; row2 < size; row2++) {
            //if any 2 rows are the same return false
            if(!(rows_are_different(board, size, row, row2)) && row != row2) {
                noDuplicates = false;
            }
        
        }
        for(int col = 0; col < size; col++) {
            for(int col2 = 0; col2 < size; col2++) {
                //if any two columns are the same return false
                if(!(cols_are_different(board, size, col, col2)) && col != col2) {
                    noDuplicates = false;
                }
            }
            
        }
    }
    return noDuplicates;
}


/**
 * --------------------------------------------------------
 * ---------- SOLVING FUNCTIONS ---------------------------
 * --------------------------------------------------------
 */

void solve_three_in_a_row(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int row,
                          bool announce) {
    for(int col = 0; col < size; col++) {
        //function only works if size > 2
        if(size > 2) {
            //checking two in a row
            //if col == size - 2, --XX, --OO
            if(col == size - 2) {
                if(board[row][col] != UNKNOWN && board[row][col] == board[row][col + 1]) {
                    if (board[row][col] == RED && board[row][col - 1] == UNKNOWN) {
                        mark_square_as(board, size, row, col - 1, opposite_color(RED), announce);
                    } else if (board[row][col] == BLUE && board[row][col - 1] == UNKNOWN) {
                        mark_square_as(board, size, row, col - 1, opposite_color(BLUE), announce);
                    }
                }
        //if col == 0, checking XX--, OO--
            } else if (col == 0) {
                if(board[row][col] != UNKNOWN && board[row][col] == board[row][col + 1]) {
                    if (board[row][col] == RED && board[row][col + 2] == UNKNOWN) {
                        mark_square_as(board, size, row, col + 2, opposite_color(RED), announce);
                    } else if (board[row][col] == BLUE && board[row][col + 2] == UNKNOWN) {
                        mark_square_as(board, size, row, col + 2, opposite_color(BLUE), announce);
                    }
                }
        //checking -XX-, -OO-, size - 2 is second to last
            } else if (col < size - 2) {
                if (board[row][col] == RED && board[row][col] == board[row][col + 1]) {
                // if there are two in a row reds, add blue on either side
                    if (board[row][col - 1] == UNKNOWN && board[row][col + 2] == UNKNOWN) {
                        mark_square_as(board, size, row, col - 1, opposite_color(RED), announce);
                        mark_square_as(board, size, row, col + 2, opposite_color(RED), announce);
                    } else if (board[row][col - 1] == UNKNOWN) {
                        mark_square_as(board, size, row, col - 1, opposite_color(RED), announce);
                    } else if (board[row][col + 2] == UNKNOWN) {
                        mark_square_as(board, size, row, col + 2, opposite_color(RED), announce);
                    }
                } else if(board[row][col] == BLUE && board[row][col] == board[row][col + 1]) {
                // if there are two in a row blues, add red on either side
                    if (board[row][col - 1] == UNKNOWN && board[row][col + 2] == UNKNOWN) {
                        mark_square_as(board, size, row, col - 1, opposite_color(BLUE), announce);
                        mark_square_as(board, size, row, col + 2, opposite_color(BLUE), announce);
                    } else if (board[row][col - 1] == UNKNOWN) {
                        mark_square_as(board, size, row, col - 1, opposite_color(BLUE), announce);
                    } else if (board[row][col + 2] == UNKNOWN) {
                        mark_square_as(board, size, row, col + 2, opposite_color(BLUE), announce);
                    }
                }
            }
        }
        if(col < size - 2) {
            //X-X-, O-O-, -X-X, O-O-(size - 2 is second to last)
            if (board[row][col] != UNKNOWN && board[row][col] == board[row][col + 2]) {
                //if two reds are sperated by an unkown, mark blue inbetween
                if (board[row][col] == RED) {
                    if (board[row][col + 1] == UNKNOWN) {
                        mark_square_as(board, size, row, col + 1, opposite_color(RED), announce);
                    }
                    //if two blues are sperated by an unkown, mark red inbetween
                } else if (board[row][col] == BLUE) {
                    if (board[row][col + 1] == UNKNOWN) {
                        mark_square_as(board, size, row, col + 1, opposite_color(BLUE), announce);
                    }
                }
            }
        }
    }
}

void solve_three_in_a_column(int board[MAX_SIZE][MAX_SIZE],
                             int size,
                             int col,
                             bool announce) {
    //all comments of board should be looked at sideways
    //(--XX) is actually -->
    //          -
    //          -
    //          X
    //          X
    for(int row = 0; row < size; row++) {
        //function only works if size > 2
        if(size > 2) {
            //checking two in a row
            //if col == size - 2 it checks --XX, --OO
            if(row == size - 2) {
                if(board[row][col] != UNKNOWN && board[row][col] == board[row + 1][col]) {
                    if (board[row][col] == RED && board[row - 1][col] == UNKNOWN) {
                        mark_square_as(board, size, row - 1, col, opposite_color(RED), announce);
                    } else if (board[row][col] == BLUE && board[row - 1][col] == UNKNOWN) {
                        mark_square_as(board, size, row - 1, col, opposite_color(BLUE), announce);
                    }
                }
        //if col == 0, checking XX--, OO--
            } else if (row == 0) {
                if(board[row][col] != UNKNOWN && board[row][col] == board[row + 1][col]) {
                    if (board[row][col] == RED && board[row + 2][col] == UNKNOWN) {
                        mark_square_as(board, size, row + 2, col, opposite_color(RED), announce);
                    } else if (board[row][col] == BLUE && board[row + 2][col] == UNKNOWN) {
                        mark_square_as(board, size, row + 2, col, opposite_color(BLUE), announce);
                    }
                }
        //checking -XX-, -OO-
            } else if (row < size - 2) {
                if (board[row][col] == RED && board[row][col] == board[row + 1][col]) {
                    // if there are two in a column reds, add blue on either side
                    if (board[row - 1][col] == UNKNOWN && board[row + 2][col] == UNKNOWN) {
                        mark_square_as(board, size, row - 1, col, opposite_color(RED), announce);
                        mark_square_as(board, size, row + 2, col, opposite_color(RED), announce);
                    } else if (board[row - 1][col] == UNKNOWN) {
                        mark_square_as(board, size, row - 1, col, opposite_color(RED), announce);
                    } else if (board[row + 2][col] == UNKNOWN) {
                        mark_square_as(board, size, row + 2, col, opposite_color(RED), announce);
                    }
                } else if(board[row][col] == BLUE && board[row][col] == board[row + 1][col]) {
                    // if there are two in a column blues, add red on either side
                    if (board[row - 1][col] == UNKNOWN && board[row + 2][col] == UNKNOWN) {
                        mark_square_as(board, size, row - 1, col, opposite_color(BLUE), announce);
                        mark_square_as(board, size, row + 2, col, opposite_color(BLUE), announce);
                    } else if (board[row - 1][col] == UNKNOWN) {
                        mark_square_as(board, size, row - 1, col, opposite_color(BLUE), announce);
                    } else if (board[row + 2][col] == UNKNOWN) {
                        mark_square_as(board, size, row + 2, col, opposite_color(BLUE), announce);
                    }
                }
            }
        }
        //X-X-, O-O-, -X-X, O-O-(size - 2 means second to last)
        if(row < size - 2) {
            if (board[row][col] != UNKNOWN && board[row][col] == board[row + 2][col]) {
                //if two reds are sperated by an unkown, mark blue inbetween
                if (board[row][col] == RED) {
                    if (board[row + 1][col] == UNKNOWN) {
                        mark_square_as(board, size, row + 1, col, opposite_color(RED), announce);
                    }
                    //if two blues are sperated by an unkown, mark red inbetween
                } else if (board[row][col] == BLUE) {
                    if (board[row + 1][col] == UNKNOWN) {
                        mark_square_as(board, size, row + 1, col, opposite_color(BLUE), announce);
                    }
                }
            }
        }
    }}


void solve_balance_row(int board[MAX_SIZE][MAX_SIZE],
                       int size,
                       int row,
                       bool announce) {
    
    int sizeLim = size - 1;
    int redCounter = 0;
    int blueCounter = 0;
    for(int col = 0; col < size; col++) {
        //counting number of reds and blues
        if(board[row][col] == RED) {
            redCounter++;
        } else if (board[row][col] == BLUE) {
            blueCounter++;
        }
        //if half the row is red, mark rest of unknown row as blue
        if(redCounter == size / DIVIDE_BY_TWO && col == sizeLim) {
            for(int col2 = 0; col2 < size; col2++) {
                if(board[row][col2] == UNKNOWN) {
                    mark_square_as(board, size, row, col2, opposite_color(RED), announce);
                }
            }
        //if half the row is blue, mark rest of unknown row as red
        } else if (blueCounter == size / DIVIDE_BY_TWO && col == sizeLim) {
            for(int col3 = 0; col3 < size; col3++) {
                if(board[row][col3] == UNKNOWN) {
                    mark_square_as(board, size, row, col3, opposite_color(BLUE), announce);
                }
            }
        }
    }
}

void solve_balance_column(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int col,
                          bool announce) {
    int sizeLim = size - 1;
    int redCounter = 0;
    int blueCounter = 0;
    for(int row = 0; row < size; row++) {
        //counting number of reds and blues
        if(board[row][col] == RED) {
            redCounter++;
        } else if (board[row][col] == BLUE) {
            blueCounter++;
        }
        //if half the column is red, mark rest of unknown column as blue
        if(redCounter == size / DIVIDE_BY_TWO && row == sizeLim) {
            for(int row2 = 0; row2 < size; row2++) {
                if(board[row2][col] == UNKNOWN) {
                    mark_square_as(board, size, row2, col, opposite_color(RED), announce);
                }
            }
        //if half the column is blue, mark rest of unknown column as red
        } else if (blueCounter == size / DIVIDE_BY_TWO && row == sizeLim) {
            for(int row3 = 0; row3 < size; row3++)
                if(board[row3][col] == UNKNOWN) {
                    mark_square_as(board, size, row3, col, opposite_color(BLUE), announce);
            }
        }
    }
}


/**
 * --------------------------------------------------------
 * ---------- GAMEPLAY FUNCTIONS --------------------------
 * --------------------------------------------------------
 */

bool board_is_solved(const int board[MAX_SIZE][MAX_SIZE], int size) {
    //if board is not valid or there is an unknown square, return false
    //else return true
    if(!(board_is_valid(board, size))) {
        return false;
    } else if (count_unknown_squares(board, size) != 0) {
        return false;
    } else {
        return true;
    }
}

bool check_valid_input(int size, int row_input, char col_input,
                       char color_char, int &row, int &col) {
    bool validInput = true;
    //check if row is inside of board
    if(!(row_input >= 1 && row_input <= size)) {
        validInput = false;
    }
    
    //check if column is inside of board
    if (!(toupper(col_input) >= 'A' && toupper(col_input) <= 'A' + size - 1)) {
        if(!(col_input >= 'A' && col_input <= 'A' + size - 1)) {
            validInput = false;
        }
    } else if (isupper(col_input) && !(col_input >= 'A' && col_input <= 'A' + size - 1)) {
        validInput = false;
    }
    //check if color is valid
    if(!(color_char == RED_LETTER || color_char == BLUE_LETTER || color_char == UNKNOWN_LETTER || color_char == tolower(RED_LETTER) || color_char == tolower(BLUE_LETTER) || color_char == tolower(UNKNOWN_LETTER))) {
        validInput = false;
    }
    
    //checks if input is valid
    if(!(validInput)) {
        cout << "Sorry, that's not a valid input." << endl;
    //gives correct row and column assignment
    } else {
        row = row_input - 1;
        if (col_input >= 'a') {
            col = col_input - 'a';
        } else if (col_input >= 'A') {
            col = col_input - 'A';
        }
        
    }
    return validInput;
}

bool check_valid_move(const int original_board[MAX_SIZE][MAX_SIZE],
                      const int current_board[MAX_SIZE][MAX_SIZE],
                      int size, int row, int col, int color) {
    //if square is not unknown return false, cannot be changed
    int copyCurrentBoard[MAX_SIZE][MAX_SIZE];
    if(original_board[row][col] != UNKNOWN) {
        cout << "Sorry, original squares cannot be changed." << endl;
        return false;
    }
    copy_board(current_board, copyCurrentBoard, size);
    copyCurrentBoard[row][col] = color;
    //if board is not valid it violates a rule, return false
    if(!(board_is_valid(copyCurrentBoard, size))) {
        cout << "Sorry, that move violates a rule." << endl;
        return false;
    } else {
        return true;
    }
}
