#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

bool hasSolution = false;   //Flag used to verify if a solution has been found
int solutionUsedMoves;   //Used to print out the result, and optimizations
/**
direction:
    1 -> UP
    2 -> DOWN
    3 -> LEFT
    4 -> RIGHT
*/

void debugGameBoard(int boardSize, std::vector<int> board) {
    int row;
    std::cout << "\n";
    for (int i = 0; i < boardSize; ++i) {
        row = i * boardSize;
        for (int j = 0; j < boardSize; ++j) {
            std::cout << board[j+row] << " ";
        }
        std::cout << "\n";
    }
}

void debugArray(std::vector<int> board) {
    std::cout << "\n";
    for (int j = 0; j < (int)board.size(); ++j) {
        std::cout << board[j] << " ";
    }
    std::cout << "\n";
}

bool checkForSolution(std::vector<int> board) {
    int n = 0;
    for(int val = 0; (val < (int)board.size()) && (n <=1); ++val) {
        if (board[val] != 0) {
            ++n;
        }
    }
    return n == 1;
}

std::vector<int> addValues(std::vector<int> values, int boardSize) {
    for (int i = 0; i < (int)values.size() - 1; ++i) {
        if (values[i] == values[i+1]) {
            values[i] = values[i] * 2;
            values.erase(values.begin() + i + 1);
        }
    }
    while ((int)values.size() < boardSize) {
        values.push_back(0);
    }
    return values;
}

std::vector<int> executeMove(int direction, int boardSize, std::vector<int> oldBoard) {
    std::vector<int> newBoard = oldBoard;
    std::vector<int> auxValues;
    int tempValue;

    //auxValues.reserve(boardSize);

    switch (direction){
        case 1:     //UP
            for (int col = 0; col < boardSize; ++col){
                for (int row = 0; row < boardSize; ++row) {
                    tempValue = newBoard[row * boardSize + col];
                    if (tempValue != 0) {
                        auxValues.push_back(tempValue);
                    }
                }
                auxValues = addValues(auxValues, boardSize);
                for (int row = 0; row < boardSize; ++row) {
                    newBoard[row * boardSize + col] = auxValues[row];
                }
                auxValues.clear();
            }
            break;

        case 2:     //DOWN
            for (int col = 0; col < boardSize; ++col){
                for (int row = boardSize - 1; row >= 0; --row) {
                    tempValue = newBoard[row * boardSize + col];
                    if (tempValue != 0) {
                        auxValues.push_back(tempValue);
                    }
                }
                auxValues = addValues(auxValues, boardSize);
                for (int row = boardSize - 1; row >= 0; --row) {
                    newBoard[row * boardSize + col] = auxValues[row];
                }
                auxValues.clear();
            }
            break;

        case 3:     //LEFT
            for (int row = 0; row < boardSize; ++row) {
                for (int col = 0; col < boardSize; ++col){
                    tempValue = newBoard[row * boardSize + col];
                    if (tempValue != 0) {
                        auxValues.push_back(tempValue);
                    }
                }
                auxValues = addValues(auxValues, boardSize);
                for (int col = 0; col < boardSize; ++col) {
                    newBoard[row * boardSize + col] = auxValues[col];
                }
                auxValues.clear();
            }

            break;

        case 4:     //RIGHT
            for (int row = 0; row < boardSize; ++row) {
                for (int col = boardSize - 1; col >= 0; --col){
                    tempValue = newBoard[row * boardSize + col];
                    if (tempValue != 0) {
                        auxValues.push_back(tempValue);
                    }
                }
                auxValues = addValues(auxValues, boardSize);
                for (int col = boardSize - 1; col >= 0; --col) {
                    newBoard[row * boardSize + col] = auxValues[col];
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
    if(checkForSolution(newBoard)){

        hasSolution = true;
        if (solutionUsedMoves > maxMoves - remainingMoves){
            solutionUsedMoves = maxMoves - remainingMoves;
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
        to keep on moving it down this way, just wasting time and resources.
        */
        return;
    }
    executeStep(remainingMoves - 1, maxMoves, boardSize, 1, newBoard);
    executeStep(remainingMoves - 1, maxMoves, boardSize, 2, newBoard);
    executeStep(remainingMoves - 1, maxMoves, boardSize, 3, newBoard);
    executeStep(remainingMoves - 1, maxMoves, boardSize, 4, newBoard);
}

void solveBoard(int maxMoves, int boardSize, std::vector<int> gameBoard) {
    hasSolution = false;                //reset the flag for the new board;
    solutionUsedMoves = maxMoves;       //set solutionUsedMoves to maxMoves

    executeStep(maxMoves - 1, maxMoves, boardSize, 1, gameBoard);
    executeStep(maxMoves - 1, maxMoves, boardSize, 2, gameBoard);
    executeStep(maxMoves - 1, maxMoves, boardSize, 3, gameBoard);
    executeStep(maxMoves - 1, maxMoves, boardSize, 4, gameBoard);

    if (hasSolution) {
        std::cout << solutionUsedMoves << "\n";
    }
    else {
        std::cout << "no solution" << "\n";
    }
}

int main() {
    int testCases;
    int boardSize;
    int totalElements;
    int maxMoves;
    int auxNumber;
    std::vector<int> gameBoard; //Data structure to represent the board itself

    std::cin >> testCases;

    for (int game = 0; game < testCases; ++game) {
        std::cin >> boardSize;
        std::cin >> maxMoves;
        totalElements = boardSize * boardSize;

        gameBoard.reserve(totalElements);
        //Read Board into Data structure
        for (int element = 0; element < totalElements; ++element) {
            std::cin >> auxNumber;
            gameBoard.push_back(auxNumber);
        }
        solveBoard(maxMoves, boardSize, gameBoard);
        gameBoard.clear(); //reset vector
    }
    return 0;
}
