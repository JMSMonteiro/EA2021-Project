#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

bool hasSolution = false;   //Flag used to verify if a solution has been found
int remainingMovesSolved;   //Used to print out the result, and optimizations
/**
direction:
    1 -> UP
    2 -> DOWN
    3 -> LEFT
    4 -> RIGHT
*/

std::vector<int> addValues(std::vector<int> values, int boardSize) {
    for (int i = 0; int i < values.size() - 1; ++i) {
        if (values[i] == values[i+1]) {
            values[i] = values[i] * 2;
            values.erase(values.begin() + i + 1);
        }
    }
    while (values.size() < boardSize) {
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
                for (int i = 0; i < boardSize; ++i) {
                    tempValue = newBoard[i*boardSize];
                    if (tempValue != 0) {
                        auxValues.push_back(tempValue);
                    }
                }
                auxValues = addValues(auxValues);
                for (int i = 0; i < auxValues.size(); ++i) {
                    newBoard[i*boardSize] = auxValues[i];
                }

            break;

        case 2:     //DOWN


            break;

        case 3:     //LEFT


            break;

        case 4:     //RIGHT


            break;

        default:
            break;
        }

        return newBoard;
}

void executeStep(int remainingMoves, int boardSize, int direction, std::vector<int> gameBoard) {
    std::vector<int> newBoard = executeMove(direction, boardSize, gameBoard);

    if (remainingMoves <= 0 || remainingMoves < remainingMovesSolved || gameBoard == newBoard) {
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
    executeStep(remainingMoves - 1, boardSize, 1, newBoard);
    executeStep(remainingMoves - 1, boardSize, 2, newBoard);
    executeStep(remainingMoves - 1, boardSize, 3, newBoard);
    executeStep(remainingMoves - 1, boardSize, 4, newBoard);
}

void solveBoard(int maxMoves, int boardSize, std::vector<int> gameBoard) {
    hasSolution = false;                //reset the flag for the new board;
    remainingMovesSolved = maxMoves;    //set remainingMovesSolved to maxMoves

    executeStep(maxMoves, boardSize, 1, gameBoard);
    executeStep(maxMoves, boardSize, 2, gameBoard);
    executeStep(maxMoves, boardSize, 3, gameBoard);
    executeStep(maxMoves, boardSize, 4, gameBoard);

    if (hasSolution) {
        std::cout << remainingMovesSolved << "\n";
    }
    else {
        std::cout << "no solution" << "\n";
    }
}

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
        //debugGameBoard(boardSize, gameBoard);
        solveBoard(maxMoves, boardsize, gameBoard);
        gameBoard.clear(); //reset vector
    }
    return 0;
}
