#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define DOWN 0
#define UP 1
#define MOD 1000000007

using uint = unsigned int;
uint arches = 0;
std::vector<std::pair<int, int>> archesDone;
std::vector<uint> table;
bool debug = true;

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
int modMul(int a, int b, int mod) {
  long long int la = modAbs(a, mod);
  long long int lb = modAbs(b, mod);
  long long int lm = mod;
  return (int)((la * lb) % lm);
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
    bool updated = false;
    // int diff = 0;
    // int midValue = 0;

    // for (int i = 1; i < blockHeight; ++i) {
    //     if (currentHeight + (blockHeight) + i > maxHeight) { break ;}
    //     if (usedPieces + 1 == blockNumber) { break; }
    //     index = (usedPieces) + ((currentHeight + i) * blockNumber);
    //     table[index] += 1;
    //     buildAscending(blockNumber, blockHeight, maxHeight, usedPieces + 1, currentHeight + i);
    // }

    for (int currentHeight = 1; currentHeight < maxHeight; ++currentHeight) {
        updated = false;
        for (int currentPiece = lastPiece; currentPiece < /*(1 + (currentHeight * (blockNumber - 2)))*/ blockNumber - 1; ++currentPiece) {
            if (currentHeight + blockHeight > maxHeight ) {
                return;
            }
            currentLevelElements = 1 + (currentPiece * (blockHeight - 2) );
            
            // if (currentHeight > (blockHeight - 1 ) * currentPiece + 1 ) {
            //     // doesn't surprass block h - 1, at least one square touches
            //     break;
            // }
            // if (currentPiece == blockNumber - 1 && currentHeight >= blockHeight) {
            //     continue;
            // }
            
            index = currentPiece + (currentHeight * blockNumber);
            val = 0;
            if (debug) {
                std::cout << "\t\t" << "pieceIndex: [" << currentPiece << "," << currentHeight << "] -> " << currentLevelElements << "\n";
                //std::cout << "\tIndex: " << index << "\n";
            }

            //IDEA
            if (currentHeight >= currentPiece + currentLevelElements) {
                continue;
            }
            //End of IDEA

            // midValue = currentPiece + (currentLevelElements / 2);
            // if (currentHeight > midValue) {
            //     // diff = (currentHeight - (currentPiece + currentLevelElements));
                
            //     // diff = index - (currentPiece + ((currentPiece + (currentLevelElements / 2) - 1) * blockNumber));
            //     //currentIndex = index - diff;
                
            //     diff = currentHeight - midValue;
            //     currentIndex = currentPiece + ((midValue - diff) * blockNumber);
                
            //     // diff = currentHeight - (currentPiece + (currentLevelElements / 2) + 1);
            //     // currentIndex = (index - (blockNumber * diff));
            //     if (debug) {
            //         std::cout << "\t[" << currentPiece<<","<<currentHeight<<"] - " << index << "\t-\t" << currentIndex << "\t| " << diff << "\n";
            //         // std::cout << index << " | " << currentIndex << "\n";
            //     }
            //     table[index] = table[currentIndex];
            //     continue;
            //     //val = table[]
            // }
            for (int i = 1; i < blockHeight; ++i) {   
                // if (index == 18) { std::cout << "\nHey\n";}
                // std::cout << "\tIndex: " << index << " <=> " << i << "\n";
                currentIndex = (index - (blockNumber * i)) - 1;
                val += currentIndex >= 0 ? table[currentIndex] : 0;
            }
            table[index] = val;
            // std::cout << "\t\tIndex: " << index << "\n";
        }

        //TODO: join these two, for debugging atm
        // if (lastPiece >= blockNumber) {
        //     return;
        // }
        // currentLevelElements = currentLevelElements * 3;
        if (!updated && currentHeight > 1 && (currentHeight + 1) % remainder) {
            // std::cout << "\tcurrHeight: " << currentHeight << "|\tRemainder: " << remainder << "\n";
            // lastPiece +=1;
            updated = true;
        }
    }

}

void makeArches2(int blockNumber, int blockHeight,int maxHeight) {
    // uint archesToAdd = 0;
    uint leftmost = 0;
    uint leftmost1 = 0;
    uint line = 1;
    uint col = 0;
    if (debug) {
        std::cout << "\n";
        printTable(blockNumber, maxHeight);
        std::cout << "\n";
    }

    for(int i = blockNumber + 1; i < maxHeight * blockNumber; ++i){
        // if (debug) std::cout<<"Line: "<<line<<" Col: "<<col<<" Val:"<<table[i]<<" Index:"<<i<<"\n";
        leftmost++;
        //int retro = i - ((blockHeight-1) * blockNumber) - (((blockHeight - 1) * blockNumber) % blockNumber);
        int retro = ((i / blockNumber) - (blockHeight - 1)) * blockNumber ;
        if (retro < 0){ retro = 0;}
        if (table[i]) {
            if (debug) std::cout << "retro = " << retro << "\n";
            for(int j = retro; j / blockNumber < i / blockNumber; ++j){
                if (j == 0) {continue;}
                leftmost1 ++;
                //if ((j % blockNumber) + (i % blockNumber) + 1 > blockNumber) {break;} 
                if (debug) std::cout << "\t\ti = " << i <<"\t\tj = " << j << "\n";
                if (table[j]){
                    arches = modAdd(arches, modMul(table[i], table[j], MOD),MOD);
                }
                if (table[j+1] == 0){
                    if(table[j + blockNumber] == 0){
                        j = j + blockNumber; 
                    if (i == 18) std::cout << "\t\t" << j << "\t\tAAAAAAAAHHHHHHHHHHHHHHHH\n";
                    }
                    else{
                        j = j + blockNumber - leftmost1;
                    } 
                    leftmost1 = 0;
                    // col = 0;
                    // line++;
                    if(table[j+1] == 0 && table[j + 1 + blockNumber] == 0 && (j+1) % blockNumber == 0){
                        if (debug) std::cout << "\n\tBREAK! j = " << j << "\n";
                        break;
                    }
                }
            }
        }
        
        if(table[i+1] == 0){
            // if (debug) std::cout << "\t\t\tI'm " << table[i+1] << " Index: " << i + 1 << "\n";
            if(table[i + blockNumber] == 0){
                // if (debug) std::cout << "old i = " << i <<"\n";
                i = i + blockNumber; 
                // if (debug)std::cout << "new i = " << i <<"\n";
            }
            else {
                // if (debug) std::cout << "old i = " << i <<"\n";
                i = i + blockNumber - leftmost;
                // if (debug) std::cout << "new i = " << i <<"\n";
            }
            leftmost = 0;
            col = 0;
            line++;
            if(table[i+1] == 0 && table[i + 1 + blockNumber]){
                if (debug) std::cout << "\nBREAK!\n";
                break;
            }
            if (debug) std::cout << "New i: " << i << "\n";
        }
        col++;
    }
        // arches = modAdd(arches, archesToAdd, MOD);
        // archesToAdd = 0;

    return;
}

void makeArches(int blockNumber, int blockHeight,int maxHeight) {
    uint aux, aux2;
    uint archesToAdd = 0;
    
    if (debug) {
        std::cout << "\n";
        printTable(blockNumber, maxHeight);
        std::cout << "\n";
    }

    for (int block = 1; block < blockNumber + 1; ++block) {
        for (int height = block; height < maxHeight - blockHeight + 1; ++height) {
            aux = table[block + (height * blockNumber)];
            if (aux) {
                for (int axheight = (height - blockHeight + 1) > 0 
                ? (height - blockHeight + 1) : 0; axheight < height; ++axheight) {
                    for (int axblock = 0; axblock + 1 + block < blockNumber; ++axblock) {
                        aux2 = table[axblock + (axheight * blockNumber)];
                        if (aux2) {
                            archesToAdd = modAdd(archesToAdd, modMul(aux2, aux, MOD), MOD);
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
    // makeArches(blockNumber, blockHeight, maxHeight);
    makeArches2(blockNumber, blockHeight, maxHeight);
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