#include <iostream>
#include <vector>
#include <algorithm>

#define DOWN 0
#define UP 1
#define MOD 1000000007

using uint = unsigned int;
uint arches = 0;


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

    if (current == blockNumber - 1 ){
        arches = modAdd(arches,1,MOD);
        return;
    }
    for(int offset = 1;offset<blockHeight;++offset){
        if (direction) {
            arc[current] = arc[current - 1] + blockHeight - offset; 
        }   
        else {
            arc[current] = arc[current - 1] - blockHeight + offset;
        }
        
        // If it reaches the n-1 block without failing any rule an arc was successfully made
    
        cur = arc[current];
        if (cur > maxHeight) {
            return;
        }
        if (cur == maxHeight) {
            buildArc(blockNumber, blockHeight, maxHeight, arc, current + 1,DOWN); // Call with DOWN ??
        }     
        else if(direction == DOWN){
            buildArc(blockNumber, blockHeight, maxHeight, arc, current + 1, DOWN);
        }
        else{
            buildArc(blockNumber, blockHeight, maxHeight, arc, current + 1, UP); 
            buildArc(blockNumber, blockHeight, maxHeight, arc, current + 1, DOWN);
        }
    }
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
    for (int j = 1; j < blockNumber; ++j){
        std::vector<uint> arc(j);
            
        if (j == 1) {
            arches = modAdd(arches,1,MOD);
        }
        else {
            arc[0] = 0;
            buildArc(j, blockHeight, maxHeight, arc, 1, UP);
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
        arches = 0;
        std::cin >> blockNumber >> blockHeight >> maxHeight;
        calculateArch(blockNumber, blockHeight, maxHeight);
        std::cout<<arches<<"\n";
    }
    
    return 0;
}