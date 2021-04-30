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
// std::vector<int> indexes;
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
    for (int j = 0; j < maxHeight; ++j) {
        for (int i = 0; i < blockNumber; ++i) {
            std::cout << table[i + j * blockNumber] << " ";
        }
        std::cout << "\n";
    }
}

void buildAscending(int blockNumber, int blockHeight, int maxHeight, int usedPieces, int currentHeight) {
    int index;
    // int auxHeight;
    // int currentPieces;
    // if (usedPieces > piecesUsed) {
    //     piecesUsed = usedPieces;
    // }

    if (usedPieces == blockNumber 
        //|| currentHeight + blockHeight >= maxHeight - 1
        // || usedPieces == resetValue 
        ){
        return;
    }
    // if (depth >=
    //  blockHeight) {
    //     std::cout << depth << " | " << blockHeight << "\n";
    //     //return;
    // }

    for (int i = 1; i < blockHeight; ++i) {
        // auxHeight = currentHeight + i;
        // currentPieces = usedPieces + 1;
        if (currentHeight + (blockHeight) + i > maxHeight) { break ;}
        if (usedPieces + 1 == blockNumber) { break; }
        index = (usedPieces) + ((currentHeight + i) * blockNumber);
        table[index] += 1;
        //archesDone.push_back(std::make_pair(currentHeight + i, usedPieces + 1));
        buildAscending(blockNumber, blockHeight, maxHeight, usedPieces + 1, currentHeight + i);
        // std::cout << "\t" << usedPieces;
        // return;
    }
}

void makeArches(int blockNumber, int blockHeight,int maxHeight) {
    // bool updatedValue = false;
    int aux, aux2;
    // int height1, usedPieces1;
    // int height2, usedPieces2;
    int archesToAdd = 0;
    // int i = 0;
    // int curr = 0;
    // std::sort(archesDone.begin(), archesDone.end(), sortbysec);
    //std::sort(archesDone.begin(), archesDone.end());
    
    // printArch();

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

    // for (std::pair<int, int>& tup : archesDone) {
    //     height1 = tup.first;
    //     usedPieces1 = tup.second;
    //     // if ((height1 + blockHeight - 1) > maxHeight) {continue;}

    //     // if (!updatedValue && resetValue == usedPieces1) {
    //     //     newResetValue = resetValue + blockHeight + 1;
    //     //     minHeight = height1;
    //     // }

    //     for(std::pair<int, int>& tup2 : archesDone) {
    //         height2 = tup2.first;
    //         usedPieces2 = tup2.second;
    //         if (height2 >= height1) {
    //             continue;
    //         }
    //         if (tup != tup2
    //             &&(height1 < maxHeight
    //             && height2 < height1 
    //             && height2 > (height1 - blockHeight)) 
    //             && usedPieces1 + usedPieces2 <= blockNumber) {
    //             // std::cout << usedPieces1 << " | " << usedPieces2 << " = " << blockNumber<< "\n";
    //             // std::cout << height1 << " | " << height2 << "\n\n";
    //             archesToAdd++;
    //             // std::cout << "\n\n\n\nHello\n\n\n\n";
    //             // std::cout << "h1: " << height1 << "\th2: " << height2 << "\n";
    //             // std::cout << "max: " << blockNumber << "\tu1: " << usedPieces1 << "\tu2: " << usedPieces2 << "\n\n";
    //         }
    //     }
    // arches = modAdd(arches, archesToAdd, MOD);
    // archesToAdd = 0;
    // }

    //archesDone.erase(std::remove_if(archesDone.begin(), archesDone.end(), isSmaller))
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