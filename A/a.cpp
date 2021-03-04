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

std::vector<std::vector<int>> executeMove(int direction, std::vector<std::vector<int>> oldBoard) {
    std::vector<std::vector<int>> newBoard = oldBoard;

    switch (direction){
        case 1:     //UP


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

void executeStep(int remainingMoves, int direction, std::vector<std::vector<int>> gameBoard) {
    std::vector<std::vector<int>> newBoard = executeMove(direction, gameBoard);

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
    executeStep(remainingMoves - 1, 1, newBoard);
    executeStep(remainingMoves - 1, 2, newBoard);
    executeStep(remainingMoves - 1, 3, newBoard);
    executeStep(remainingMoves - 1, 4, newBoard);
}

void solveBoard(int maxMoves, std::vector<std::vector<int>> gameBoard) {
    hasSolution = false;                //reset the flag for the new board;
    remainingMovesSolved = maxMoves;    //set remainingMovesSolved to maxMoves

    executeStep(maxMoves, 1, gameBoard);
    executeStep(maxMoves, 2, gameBoard);
    executeStep(maxMoves, 3, gameBoard);
    executeStep(maxMoves, 4, gameBoard);

    if (hasSolution) {
        std::cout << remainingMovesSolved << "\n";
    }
    else {
        std::cout << "no solution" << "\n";
    }
}


int main() {
    int testCases;
    int boardSize;
    int maxMoves;
    int auxNumber;
    std::vector<std::vector<int>> gameBoard; //Data structure to represent the board itself

    std::cin >> testCases;

    for (int i = 0; i < testCases; ++i) {
        std::cin >> boardSize;
        std::cin >> maxMoves;

        //Read Board into Data structure
        for (int row = 0; row < boardSize; ++row) {
            //gameBoard.push_back(std::vector<int>);
            for (int column = 0; column < boardSize; ++column) {
                std::cin >> auxNumber;

                //Insert auxNumber into data structure position [row][column]
            }
        }
        solveBoard(maxMoves, gameBoard);
    }
    return 0;
}
