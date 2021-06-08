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
std::vector<long> table;
bool debug = !true;

long modAbs(long a, long mod) {  
    return ((a % mod) + mod) % mod;
}
long modAdd(long a, long b, long mod) {  
    return (modAbs(a, mod) + modAbs(b, mod)) % mod;
}
long modSub(long a, long b, long mod) {  
    return modAdd(a, -b, mod);
}
long modMul(long a, long b, long mod) {
  long long int la = modAbs(a, mod);
  long long int lb = modAbs(b, mod);
  long long int lm = mod;
  return (long)((la * lb) % lm);
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
 
    for (int currentHeight = 1; currentHeight < maxHeight; ++currentHeight) {
        updated = false;
        for (int currentPiece = lastPiece; currentPiece < /*(1 + (currentHeight * (blockNumber - 2)))*/ blockNumber - 1; ++currentPiece) {
            if (currentHeight + blockHeight > maxHeight ) {
                return;
            }
            currentLevelElements = 1 + (currentPiece * (blockHeight - 2) );
            
            index = modAdd(currentPiece,modMul(currentHeight,blockNumber,MOD),MOD);
            val = 0;
            if (debug) {
                std::cout << "\t\t" << "pieceIndex: [" << currentPiece << "," << currentHeight << "] -> " << currentLevelElements << "\n";
            }

            if (currentHeight >= currentPiece + currentLevelElements) {
                continue;
            }

            for (int i = 1; i < blockHeight; ++i) {   
                currentIndex = (index - (blockNumber * i)) - 1;
                val += currentIndex >= 0 ? table[currentIndex] : 0;
            }
            table[index] = modAdd(table[index],val,MOD);
        }

       
        if (!updated && currentHeight > 1 && (currentHeight + 1) % remainder) {
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
    uint first = 0;
    uint jfirst = 0;
    if (debug) {
        std::cout << "\n";
        printTable(blockNumber, maxHeight);
        std::cout << "\n";
    }
 
    for(int i = blockNumber + 1; i < maxHeight*blockNumber;++i){    

        if (debug) std::cout<<"I " <<"Line: "<<line<<" Col: "<<col<<" Val:"<<table[i]<<" i: "<<i<<"\n";
        if(leftmost == 0)  first = i;
        leftmost++;
        leftmost1 = 0;
        int retro = ((i / blockNumber) - (blockHeight - 1)) * blockNumber ;
        if (retro <= 0){ retro = 0;}
        else {retro += 1;}
        if(table[i]){

                if (debug) std::cout << "retro = " << retro << "\n";
                for(int j = retro; j / blockNumber < i / blockNumber; ++j){
                    if (table[j] == 0) {continue;}
                    if(leftmost1 == 0)  jfirst = j;
                    leftmost1 ++;
                    if ((j % blockNumber) + (i % blockNumber) >= blockNumber - 1) {continue;} 
                     if (debug) std::cout << "\t\ti = " << i <<"\t\tj = " << j << "\n";
                     if (table[j]){
                            arches = modAdd(arches, modMul(table[i], table[j], MOD),MOD);
                    }
                    if (table[j+1] == 0){
                        if(table[j + blockNumber - (j-jfirst)] == 0){
                            j = j + blockNumber - (j-jfirst); 
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
            if(table[i + blockNumber - (i-first)] == 0){
                i = i + blockNumber - (i-first); 
            }
            else{
                i = i + blockNumber - leftmost;
            }
            leftmost = 0;
            col = 0;
            line++;
            if(table[i+1] == 0 && table[i + 1 + blockNumber]){
                if (debug) std::cout << "\nBREAK!\n";
                break;
            }
        }
        col++;
    } 
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
        std::cin >> blockNumber >> blockHeight >> maxHeight;
        table.resize((blockNumber) * (maxHeight), 0);
        calculateArch(blockNumber, blockHeight, maxHeight);
        table.clear();
        std::cout<<arches<<"\n";
    }
    return 0;
}