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
            std::cout << table[i + j * blockNumber] << "\t";
        }
        std::cout << "\n";
    }
}

void buildAscending(int blockNumber, int blockHeight, int maxHeight) {
    int lastPiece = 1;
    int currentLevelElements = 1;
    int index = 0;
    int currentIndex = 0;
    int val = 0;
    int remainder = blockHeight - 1;

    // for (int i = 1; i < blockHeight; ++i) {
    //     if (currentHeight + (blockHeight) + i > maxHeight) { break ;}
    //     if (usedPieces + 1 == blockNumber) { break; }
    //     index = (usedPieces) + ((currentHeight + i) * blockNumber);
    //     table[index] += 1;
    //     buildAscending(blockNumber, blockHeight, maxHeight, usedPieces + 1, currentHeight + i);
    // }

    for (int currentHeight = 1; currentHeight < maxHeight; ++currentHeight) {
        for (int currentPiece = lastPiece; currentPiece < /*(1 + (currentHeight * (blockNumber - 2)))*/ blockNumber; ++currentPiece) {
            // if (currentHeight > (blockHeight - 1 ) * currentPiece + 1 ) {
            //     // doesn't surprass block h - 1, at least one square touches
            //     break;
            // }
            // if (currentPiece == blockNumber - 1 && currentHeight >= blockHeight) {
            //     continue;
            // }
            
            index = currentPiece + (currentHeight * blockNumber);
            val = 0;
            //std::cout << "\tIndex: " << index << "\n";
            for (int i = 0; i < blockNumber; ++i) {   
                currentIndex = (index - (blockNumber * (i + 1))) - 1;
                val += currentIndex >= 0 ? table[currentIndex] : 0;
            }
            table[index] = val;
        }

        //TODO: join these two, for debugging atm
        // if (lastPiece >= blockNumber) {
        //     return;
        // }
        if (currentHeight + blockHeight >= maxHeight - 1) {
            return;
        }
        currentLevelElements = currentLevelElements * 3;
        if (currentHeight > 1 && currentHeight + 1 % remainder) {
            //lastPiece +=1;
        }
    }

}

void makeArches(int blockNumber, int blockHeight,int maxHeight) {
    int aux, aux2;
    int archesToAdd = 0;
    
    // std::cout << "\n";
    printTable(blockNumber, maxHeight);
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
    table[0] = 1;
    // archesDone.push_back(std::make_pair(0, 1));
    buildAscending(blockNumber, blockHeight, maxHeight);
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