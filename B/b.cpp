#include <iostream>
#include <vector>
#include <algorithm>

#define DOWN 0
#define UP 1

using uint = unsigned int;
uint arches = 0;

// Que é que a gente faz com isto ??? xD
int modAbs(int a, int mod) {  
    return ((a % mod) + mod) % mod;
}
int modAdd(int a, int b, int mod) {  
    return (modAbs(a, mod) + modAbs(b, mod)) % mod;
}
int modSub(int a, int b, int mod) {  
    return modAdd(a, -b, mod);
}

void buildArc(int blockNumber, int blockHeight, int maxHeight, std::vector<uint> arc, int current, bool direction) {
    int cur;

    if (current == blockNumber - 2){
        arches++;
        return;
    }

    // Refix for more than 1 block insertions
    if (direction) {
        arc[current] = arc[current - 1] + blockHeight - 1; 
    }   
    else {
        arc[current] = arc[current - 1] - blockHeight + 1;
    }
    
    // If it reaches the n-2 block without failing any rule an arc was successfully made
 
    cur = arc[current];
    if (cur > maxHeight) {
        return;
    }
    if (cur == maxHeight) {
        buildArc(blockNumber, blockHeight, maxHeight, arc, current + 1,DOWN); // Call with DOWN ??
    }     
    else {
        buildArc(blockNumber, blockHeight, maxHeight, arc, current + 1, UP);
        buildArc(blockNumber, blockHeight, maxHeight, arc, current + 1, DOWN);
    }
}

void calculateArch(int blockNumber, int blockHeight, int maxHeight) {
    //If block height == room height    => Impossible (blocks can't go up)
    //If blockNumber < 3                => Impossible (not enough blocks)
    if (blockHeight >= maxHeight || blockNumber < 3) {
        std::cout << 0 << "\n";
        return;
    }
    //If block height == maxHeight - 1, only one unique arch can be created
    else if (blockHeight == (maxHeight - 1) && blockNumber >= 3) {
        std::cout << 1 << "\n";
        return;
    }
    for (int j = 2; j < blockNumber; ++j){
        std::vector<uint> arc(j);
            
        if (j == 2) {
            arches++;
        }
        else {
            arc[0] = 0;
            arc[1] = blockHeight; // needs change if second and second to last can have more than 1 block
            arc[j-2] = blockHeight;
            arc[j-1] = 0;
            buildArc(blockNumber, blockHeight, maxHeight, arc, 2, UP);
        }
    }
}


int main() {
    //Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    //End of Fast(er) I/O

    int testCases, blockNumber, blockHeight, maxHeight;
    std::cin >> testCases;

    for (int i = 0; i < testCases; ++i){
        std::cin >> blockNumber >> blockHeight >> maxHeight;
        calculateArch(blockNumber, blockHeight, maxHeight);
    }
    return 0;
}