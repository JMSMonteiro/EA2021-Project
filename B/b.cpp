#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

#define DOWN 0
#define UP 1
#define MOD 1000000007

using uint = unsigned int;
uint arches = 0;
std::vector<std::tuple<int, int>> archesDone;
std::vector<int> indexes;

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
        a = std::get<0>(archesDone[i]);
        b = std::get<1>(archesDone[i]);
        std::cout << "<" << a << "," << b << ">\n";
    }
}

void printArchN(int i) {
    int a, b;
    a = std::get<0>(archesDone[i]);
    b = std::get<1>(archesDone[i]);
    std::cout << "\n<" << a << "," << b << ">\n";
}

void buildAscending(int blockNumber, int blockHeight, int maxHeight, int usedPieces, int currentHeight) {
    int auxHeight;
    int currentPieces;

    if (usedPieces == blockNumber || currentHeight + blockHeight >= maxHeight - 1) {
        return;
    }
    // if (std::get<0>(archesDone[usedPieces]) == blockNumber) {
    //     return;
    // }

    for (int i = 1; i < blockHeight; ++i) {
        auxHeight = currentHeight + i;
        currentPieces = usedPieces + 1;
        archesDone.push_back(std::make_tuple(auxHeight, currentPieces));
        buildAscending(blockNumber, blockHeight, maxHeight, currentPieces, auxHeight);
    }

    
}

void makeArches(int blockNumber, int blockHeight) {
    int height1, usedPieces1;
    int height2, usedPieces2;
    int archesToAdd = 0;
    int i = 0;
    int curr = 0;
    std::sort(archesDone.begin(), archesDone.end());

    for(int n = 0; n < (int)archesDone.size(); ++n) {
        i = std::get<0>(archesDone[n]);
        
        // printArchN(n);
        if (i == curr) {
            indexes.push_back(n);
            curr += 1;
        }
    }

    // for (int x : indexes) {
    //     std::cout << "\t" << x << "\n";
    // }


    for (std::tuple<int, int> tup : archesDone) {
        height1 = std::get<0>(tup);
        usedPieces1 = std::get<1>(tup);

        for(std::tuple<int, int> tup2 : archesDone) {
            height2 = std::get<0>(tup2);
            usedPieces2 = std::get<1>(tup2);
            if (height2 >= height1) {
                break;
            }
            if ((height2 < height1 
                && height2 > (height1 - blockHeight)) 
                && usedPieces1 + usedPieces2 <= blockNumber) {
                archesToAdd++;
                // std::cout << "\n\n\n\nHello\n\n\n\n";
                // std::cout << "h1: " << height1 << "\th2: " << height2 << "\n";
                // std::cout << "max: " << blockNumber << "\tu1: " << usedPieces1 << "\tu2: " << usedPieces2 << "\n\n";
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
    archesDone.push_back(std::make_tuple(0, 1));
    buildAscending(blockNumber, blockHeight, maxHeight, 1, 0);
    makeArches(blockNumber, blockHeight);
}


int main() {
    //Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
    // std::ios_base::sync_with_stdio(0);
    // std::cin.tie(0);
    //End of Fast(er) I/O

    int testCases, blockNumber, blockHeight, maxHeight;
    
    std::cin >> testCases;

    for (int i = 0; i < testCases; ++i){
        arches = 0;
        archesDone.clear();
        indexes.clear();
        std::cin >> blockNumber >> blockHeight >> maxHeight;
        calculateArch(blockNumber, blockHeight, maxHeight);
        // printArch();
        std::cout<<arches<<"\n";
    }
    
    return 0;
}