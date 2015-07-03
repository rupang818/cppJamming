/*
 * Assignment #1: Life
 * Course: CS 106B
 * Name: Jihoon kim
 * Date: 04/04/2015
 * Description: Enable a console to play the Game of Life,
 *              using switches a/t/q to dictate the console behavior
 */

// References
// in main(): setConsoleClearEnabled(true) - used to clear out the console properly (Thanks to Laurence Moroney)

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
using namespace std;

const char UNOCCUPIED = '-';
const char OCCUPIED = 'X';

// Function prototypes
int checkNeighbors(Grid<char>& board, int row, int col);
Grid<char> updateGrid(Grid<char>& input_grid);
Grid<char>& animateGrid (Grid<char>& g);
Grid<char> getGridFromFile(ifstream& input);
void printWelcome();
void selectAction(Grid<char>& grid);

/*
 * Implementation notes by Jihoon Kim
 * name:     checkNeighbors
 * purpose:  returns the number of neighbors for the given Grid cell
 * input:    Grid reference to board, current row and current column
 * output:   int count of the neighbors
 */
int checkNeighbors(Grid<char>& board, int row, int col) {
    // check the row,col wrt bounds. If out of bounds, exit
    board.inBounds(row, col);

    // determine the row,col min/max
    int row_min, col_min, row_max, col_max;
    (row > 0) ? row_min = row - 1 : row_min = row;
    (col > 0) ? col_min = col - 1 : col_min = col;
    (row < board.numRows() - 1) ? row_max = row + 1 : row_max = row;
    (col < board.numCols() - 1) ? col_max = col + 1 : col_max = col;

    // count the number of neighbors
    int nei_count = 0;
    for (int i = row_min; i <= row_max; i++) { //row
        for (int j = col_min; j <= col_max; j++) { //col
            if (board[i][j] == OCCUPIED && !(i == row && j == col)) {
                    nei_count++;
            }
        }
    }

    return nei_count;
}

/*
 * Implementation notes by Jihoon Kim
 * name:     updateGrid
 * purpose:  updates the grid, given the interpreted neighbor count Grid
 * input:    Grid reference to board with the number of neighbors annotated
 * output:   Grid structure of the next generation
 */
Grid<char> updateGrid(Grid<char>& input_grid) {
    int numCols = input_grid.numCols();
    int numRows = input_grid.numRows();

    Grid<char> return_grid(numRows,numCols);
    int occupancy, neighbor_count;
    char bacteria;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
             neighbor_count = checkNeighbors(input_grid, i, j);
             (input_grid[i][j] == UNOCCUPIED) ? occupancy = 0 : occupancy = 1;

             // neighbor_count 0 or 1 -> dies
             // neighbor_count 4+ -> dies (of overcrowding)
             if (neighbor_count <= 1 || neighbor_count >= 4) {
                 bacteria = UNOCCUPIED;
             } else if (neighbor_count == 2) {
                 if (occupancy == 1) {
                     bacteria = OCCUPIED;  // 2 neighbors & OCCUPIED = stays alive
                 } else {
                     bacteria = UNOCCUPIED;  // 2 neighbors & UNOCCUPIED = stays dead
                 }
             } else if (neighbor_count == 3) {
                 bacteria = OCCUPIED;     // 3 neighbors & OCCUPIED/UNOCCUPIED = lives
             }

             return_grid[i][j] = bacteria;

             cout << return_grid[i][j];
        }
        cout << endl;
    }
    return return_grid;
}

/*
 * Implementation notes by Jihoon Kim
 * name:     animateGrid
 * purpose:  Enables the animation of the board, given frame count
 * input:    Grid reference to board
 * output:   Grid structure of the next generation (after "frame" number of generations)
 */
Grid<char>& animateGrid (Grid<char>& g) {
    int frames;
    frames = getInteger("How many frames? ");

    for (int i = 0; i < frames; i++) {
        clearConsole();
        g = updateGrid(g);
        pause(50);
    }

    return g;
}

/*
 * Implementation notes by Jihoon Kim
 * getGridFromFile
 * purpose: Read in the Grid structure from the input file
 * input:   input .txt file provided
 * output:  Grid structure with the string elements,
 *           '-' denoting UNOCCUPIED space
 *           'X' denoting the OCCUPIED
 */
Grid<char> getGridFromFile(ifstream& input) {
    string line;
    int fileLineCnt = 0, row = 0;
    int* dimension = new int(2); // row=dimension[0]; col=dimension[1]
    Grid<char> lifeBoard;

    while (getline(input, line) && !line.empty() && row < dimension[0]) {
        // get the size for the board and resize accordingly
        if (fileLineCnt == 0 || fileLineCnt == 1) {
            dimension[fileLineCnt] = stringToInteger(line); //5\n9 -> dimension* = {5 9}
        } else if (row < 1) {
            lifeBoard.resize(dimension[0], dimension[1]); //only resize once
        }

        // Filter the lines with gibberish and print the valid lines
        if (line.at(0) == UNOCCUPIED || line.at(0) == OCCUPIED) {
            for (int col = 0; col < dimension[1]; col++) {
                lifeBoard[row][col] = line.at(col);
                cout << lifeBoard[row][col];
            }
            cout << endl;
            ++row;
        }

        ++fileLineCnt;
    }


    return lifeBoard; //return the reference to the Grid object
}

/*
 * Implementation notes by Jihoon Kim
 * name:     printWelcome
 * function: prints the welcome headers
 * input:    none
 * output:   none
 */
void printWelcome() {
    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies."<< endl;
    cout << endl;
}

/*
 * Implementation notes by Jihoon Kim
 * name:     selectAction
 * function: selects the action based on the keyword specified by the user
 * input:    Grid reference
 * output:   none
 */
void selectAction(Grid<char>& grid) {
    string action;

    while (action != "q") {
        action = getLine("a)nimate, t)ick, q)uit? ");
        transform(action.begin(), action.end(), action.begin(), ::tolower);

        if (action == "t") {
            grid = updateGrid(grid);      // update the grid
        } else if (action == "a") {
            grid = animateGrid(grid);
        } else if (action != "q") {
            cout << "Invalid choice; please try again." << endl;
        }
    }
}

/*
 * Implementation notes by Jihoon Kim
 * name:     main
 * function: main cockpit for the source code to run
 * input:    none
 * output:   integer value indicating the success/failure
 */
int main() {
    setConsoleClearEnabled(true);

    ifstream input;
    Grid<char> grid;

    printWelcome();

    promptUserForFile(input, "Grid input file name?");
    grid = getGridFromFile(input);
    input.close();

    selectAction(grid);

    cout << "Have a nice Life!" << endl;
    return 0;
}
