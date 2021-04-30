#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

#define DOWN 0
#define UP 1
#define MOD 1000000007

using uint = unsigned int;
uint arches = 0;
std::vector<std::pair<int, int>> archesDone;
std::vector<uint> table;
int lastPieceUsed = 0;
int piecesUsed = 0;
int resetValue = 0;
int newResetValue = 0;
int minHeight = 0;

bool sortbysec(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return (a.second > b.second);
}
// bool isSmaller(const std::pair<int, int>& a, const std::pair <int, int>& b) {
//     return (std::get<0>);
// }

int modAbs(int a, int mod) {  
    return ((a % mod) + mod) % mod;
}
int modAdd(int a, int b, int mod) {  
    return (modAbs(a, mod) + modAbs(b, mod)) % mod;
}
int modSub(int a, int b, int mod) {  
    return modAdd(a, -b, mod);
}

void printArch() {
    int a, b;
    for (int i = 0; i < (int)archesDone.size(); ++i) {
        a = archesDone[i].first;
        b = archesDone[i].second;
        std::cout << "<" << a << "," << b << ">\n";
    }
}

void printArchN(int i) {
    int a, b;
    a = archesDone[i].first;
    b = archesDone[i].second;
    std::cout << "\n<" << a << "," << b << ">\n";
}

void printTable(int blockNumber, int maxHeight) {
    for (int i = 0; i < blockNumber; ++i) {
        for (int j = 0; j < maxHeight; ++j) {
            std::cout << table[i + j * blockNumber] << "\t";
        }
        std::cout << "\n";
    }
}

void buildAscending(int blockNumber, int blockHeight, int maxHeight, int usedPieces, int currentHeight) {
    int index;

    if (usedPieces == blockNumber){
        return;
    }

    for (int i = 1; i < blockHeight; ++i) {
        if (currentHeight + (blockHeight) + i > maxHeight) { break ;}
        if (usedPieces + 1 == blockNumber) { break; }
        index = (usedPieces) + ((currentHeight + i) * blockNumber);
        table[index] += 1;
        buildAscending(blockNumber, blockHeight, maxHeight, usedPieces + 1, currentHeight + i);
    }
}

void makeArches(int blockNumber, int blockHeight,int maxHeight) {
    int aux, aux2;
    int archesToAdd = 0;
    
    // std::cout << "\n";
    // printTable(blockNumber, maxHeight);
    // std::cout << "\n";

    for (int block = 1; block < blockNumber; ++block) {
        for (int height = 0; height < maxHeight; ++height) {
            aux = table[block + (height * blockNumber)];
            if (aux) {
                for (int axheight = (height - blockHeight + 1) > 0 
                ? (height - blockHeight + 1) : 0; axheight < height; ++axheight) {
                    for (int axblock = 0; axblock + 1 + block < blockNumber; ++axblock) {
                        aux2 = table[axblock + (axheight * blockNumber)];
                        if (aux2) {
                            archesToAdd += aux2 * aux;
                        }
                    }
                }
            }
            if (height > ((block + 1) * (blockHeight) ) + 1) {
                break;
            }
        }
        arches = modAdd(arches, archesToAdd, MOD);
        archesToAdd = 0;
    }

    return;
}

void calculateArch(int blockNumber, int blockHeight, int maxHeight) {
    //If block height == room height    => Impossible (blocks can't go up)
    //If blockNumber < 3                => Impossible (not enough blocks)
    if (blockHeight >= maxHeight || blockNumber < 3) {
        arches = 0;
        return;
    }
    //If block height == maxHeight - 1, only one unique arch can be created
    else if (blockHeight == (maxHeight - 1) && blockNumber >= 3) {
        arches = 1;
        return;
    }
    table[0 + 0 * blockNumber] += 1;
    archesDone.push_back(std::make_pair(0, 1));
    resetValue = blockHeight + 1;
    buildAscending(blockNumber, blockHeight, maxHeight, 1, 0);
    makeArches(blockNumber, blockHeight, maxHeight);
}


int main() {
    //Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    //End of Fast(er) I/O

    int testCases, blockNumber, blockHeight, maxHeight;
    
    std::cin >> testCases;

    for (int i = 0; i < testCases; ++i){
        arches = 0;
        table.clear();
        archesDone.clear();
        // indexes.clear();
        std::cin >> blockNumber >> blockHeight >> maxHeight;
        table.resize((blockNumber) * (maxHeight), 0);
        calculateArch(blockNumber, blockHeight, maxHeight);
        // printArch();
        std::cout<<arches<<"\n";
    }
    
    return 0;
}