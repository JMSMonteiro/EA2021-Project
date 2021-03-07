#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

bool hasSolution = false;       //Flag used to verify if a solution has been found
bool canMoveSameDir = false;    //If doing the same move will affect the board elements
int solutionUsedMoves;          //Used to print out the result, and optimizations
/**
direction:
    1 -> UP
    2 -> DOWN
    3 -> LEFT
    4 -> RIGHT
*/

bool checkForSolution(std::vector<int> board) {
    int n = 0;
    //Goes through the array, checks if only one element has value (Puzzle solved)
    for(int val = 0; (val < (int)board.size()) && (n <=1); ++val) {
        if (board[val] != 0) {
            ++n;
        }
    }
    return n == 1;  //If n > 1 => Puzzle is not solved
}

std::vector<int> addValues(std::vector<int> values, int boardSize) {
    for (int i = 0; i < (int)values.size() - 1; ++i) {  //for each value in vector
        if (values[i] == values[i+1]) {                 //Values only add up if they're equal
            values[i] = values[i] * 2;                  //Value addition == value * 2
            values.erase(values.begin() + i + 1);       //Deletes added value
        }
        //Checks if there's any two numbers that can be added next iteration
        if (i > 0 && values[i] == values[i-1]) {
            canMoveSameDir = true;
        }
    }
    //Resizes the current row/column to the board size, fills added values with 0
    values.resize(boardSize, 0);
    return values;
}

std::vector<int> executeMove(int direction, int boardSize, std::vector<int> newBoard) {
    std::vector<int> auxValues; //Current row/column non zero elements
    int currentValue;
    canMoveSameDir = false;     //Resets variable, if true will be updated in addValues(...)

    switch (direction){
        case 1:     //UP
            //Goes through every column, left to right, adding to the auxValues
            // vector every non 0 element from top to bottom
            for (int col = 0; col < boardSize; ++col){
                for (int row = 0; row < boardSize; ++row) {
                    currentValue = newBoard[row * boardSize + col];
                    if (currentValue != 0) {
                        auxValues.push_back(currentValue);
                    }
                }
                if (!auxValues.empty()) {   //If the current row/column has any non-zero element
                    //Performs the row/column elements addition (if possible)
                    auxValues = addValues(auxValues, boardSize);
                    for (int row = 0; row < boardSize; ++row) {
                        newBoard[row * boardSize + col] = auxValues[row];
                    }
                }
                auxValues.clear();
            }
            break;

        case 2:     //DOWN
            //Goes through every column, left to right, adding to the auxValues
            // vector every non 0 element from bottom to top
            for (int col = 0; col < boardSize; ++col){
                for (int row = boardSize - 1; row >= 0; --row) {
                    currentValue = newBoard[row * boardSize + col];
                    if (currentValue != 0) {
                        auxValues.push_back(currentValue);
                    }
                }
                if (!auxValues.empty()) {   //If the current row/column has any non-zero element
                    //Performs the row/column elements addition (if possible)
                    auxValues = addValues(auxValues, boardSize);
                    for (int row = boardSize - 1; row >= 0; --row) {
                        newBoard[row * boardSize + col] = auxValues[row];
                    }
                }
                auxValues.clear();
            }
            break;

        case 3:     //LEFT
            //Goes through every line, top to bottom, adding to the auxValues
            // vector every non 0 element from left to right
            for (int row = 0; row < boardSize; ++row) {
                for (int col = 0; col < boardSize; ++col){
                    currentValue = newBoard[row * boardSize + col];
                    if (currentValue != 0) {
                        auxValues.push_back(currentValue);
                    }
                }
                if (!auxValues.empty()) {   //If the current row/column has any non-zero element
                    //Performs the row/column elements addition (if possible)
                    auxValues = addValues(auxValues, boardSize);
                    for (int col = 0; col < boardSize; ++col) {
                        newBoard[row * boardSize + col] = auxValues[col];
                    }
                }
                auxValues.clear();
            }

            break;

        case 4:     //RIGHT
            //Goes through every line, top to bottom, adding to the auxValues
            // vector every non 0 element from right to left
            for (int row = 0; row < boardSize; ++row) {
                for (int col = boardSize - 1; col >= 0; --col){
                    currentValue = newBoard[row * boardSize + col];
                    if (currentValue != 0) {
                        auxValues.push_back(currentValue);
                    }
                }
                if (!auxValues.empty()) {   //If the current row/column has any non-zero element
                    //Performs the row/column elements addition (if possible)
                    auxValues = addValues(auxValues, boardSize);
                for (int col = boardSize - 1; col >= 0; --col) {
                    newBoard[row * boardSize + col] = auxValues[col];
                }
            }
                auxValues.clear();
            }
            break;

        default:
            break;
        }
        return newBoard;
}

void executeStep(int remainingMoves, int maxMoves, int boardSize, int direction, std::vector<int> gameBoard) {
    std::vector<int> newBoard = executeMove(direction, boardSize, gameBoard);
    if(checkForSolution(newBoard)){     //Checks if the puzzle has been solved with the current move
        hasSolution = true;
        if (solutionUsedMoves > maxMoves - remainingMoves){ //If current best solution is worse than new solution
            solutionUsedMoves = maxMoves - remainingMoves;  //Calculates the moves used to reach solution
        }
        return;
    }

    if (remainingMoves <= 0 || maxMoves - remainingMoves >= solutionUsedMoves || gameBoard == newBoard) {
        /**
        Optimization logic:
        - If reaches max number of moves, stops there.
        - Also, if there has been found a solution, with "n" moves left, there's
        no point in pursuing solutions that use more moves than the current
        "best" solution.
        - If the board didn't change at all, there's no point in trying
        to keep on moving it down this way.
        */
        return;
    }
    switch (direction) {
        case 1:     //UP
            if (canMoveSameDir) {
                executeStep(remainingMoves - 1, maxMoves, boardSize, 1, newBoard);  //Execute move UP
            }
            executeStep(remainingMoves - 1, maxMoves, boardSize, 3, newBoard);  //Execute move LEFT
            executeStep(remainingMoves - 1, maxMoves, boardSize, 4, newBoard);  //Execute move RIGHT
            executeStep(remainingMoves - 1, maxMoves, boardSize, 2, newBoard);  //Execute move DOWN
            break;
        case 2:     //DOWN
            if (canMoveSameDir) {
                executeStep(remainingMoves - 1, maxMoves, boardSize, 2, newBoard);  //Execute move DOWN
            }
            executeStep(remainingMoves - 1, maxMoves, boardSize, 3, newBoard);  //Execute move LEFT
            executeStep(remainingMoves - 1, maxMoves, boardSize, 4, newBoard);  //Execute move RIGHT
            executeStep(remainingMoves - 1, maxMoves, boardSize, 1, newBoard);  //Execute move UP
            break;
        case 3:     //LEFT
            if (canMoveSameDir) {
                executeStep(remainingMoves - 1, maxMoves, boardSize, 3, newBoard);  //Execute move LEFT
            }
            executeStep(remainingMoves - 1, maxMoves, boardSize, 1, newBoard);  //Execute move UP
            executeStep(remainingMoves - 1, maxMoves, boardSize, 2, newBoard);  //Execute move DOWN
            executeStep(remainingMoves - 1, maxMoves, boardSize, 4, newBoard);  //Execute move RIGHT
            break;
        case 4:     //RIGHT
            if (canMoveSameDir) {
                executeStep(remainingMoves - 1, maxMoves, boardSize, 4, newBoard);  //Execute move RIGHT
            }
            executeStep(remainingMoves - 1, maxMoves, boardSize, 1, newBoard);  //Execute move UP
            executeStep(remainingMoves - 1, maxMoves, boardSize, 2, newBoard);  //Execute move DOWN
            executeStep(remainingMoves - 1, maxMoves, boardSize, 3, newBoard);  //Execute move LEFT
            break;
    }
}

void solveBoard(int maxMoves, int boardSize, std::vector<int> gameBoard, bool isSolvable) {
    bool inputIsSolved = checkForSolution(gameBoard);   //Check if board is already solved
    hasSolution = inputIsSolved;                        //Reset the flag for the new board
    solutionUsedMoves = inputIsSolved ? 0 : maxMoves;   //Set solutionUsedMoves to maxMoves

    if(!hasSolution && isSolvable) {    //If the puzzle is solvable && is not already solved
        executeStep(maxMoves - 1, maxMoves, boardSize, 1, gameBoard);   //Execute move UP
        executeStep(maxMoves - 1, maxMoves, boardSize, 2, gameBoard);   //Execute move DOWN
        executeStep(maxMoves - 1, maxMoves, boardSize, 3, gameBoard);   //Execute move LEFT
        executeStep(maxMoves - 1, maxMoves, boardSize, 4, gameBoard);   //Execute move RIGHT
    }

    if (hasSolution) {  //If board has a solution, prints the number of moves to achieve it
        std::cout << solutionUsedMoves << "\n";
    }
    else {              //If board is unsolvable, prints "no solution"
        std::cout << "no solution" << "\n";
    }
}

int main() {
    int testCases;              //# of test cases
    int boardSize;              //# of rows and columns | board size
    int totalElements;          //Total elements in a board (#columns * #rows)
    int maxMoves;               //Max moves allowed to the player
    int currentInput;           //Variable to read the input to
    int inputsSum;              //Total sum of the board elements
    int power;                  //Variable to calculate the powers of 2
    bool isSolvable = false;    //If the board is solvable > can reduce the board to one tile
    std::vector<int> gameBoard; //Data structure to represent the board itself

    std::cin >> testCases;

    //Main function Loop
    for (int game = 0; game < testCases; ++game) {
        //Read boardsize and max moves for the current board
        std::cin >> boardSize;
        std::cin >> maxMoves;
        totalElements = boardSize * boardSize;  //Calculates the number of elements in the board
        inputsSum = 0;                          //Inputs sum is reset to 0
        power = 2;                              //Power is reset to 2 (2^1)

        gameBoard.reserve(totalElements);
        //Read Board into Data structure
        for (int element = 0; element < totalElements; ++element) {
            std::cin >> currentInput;
            gameBoard.push_back(currentInput);
            inputsSum += currentInput;
        }
        //Checks if the board is solvable => The sum of every element in the
        // board is a power of 2
        while(power < inputsSum) {
            power = power * 2;
            if (power == inputsSum) {
                isSolvable = true;
            }
        }
        solveBoard(maxMoves, boardSize, gameBoard, isSolvable);
        gameBoard.clear(); //reset vector
    }
    return 0;
}
