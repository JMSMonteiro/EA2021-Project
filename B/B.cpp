#include <iostream>
#include <vector>
#include <algorithm>

#define DOWN 0
#define UP 1

using uint = unsigned int;
uint arcs = 0;


// Que é que a gente faz com isto ??? xD
int mod_abs(int a, int mod) {  return ((a % mod) + mod) % mod;}
int mod_add(int a, int b, int mod) {  return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;}
int mod_sub(int a, int b, int mod) {  return mod_add(a, -b, mod);}


void buildArc(int n,int h,int max_h,std::vector<uint> arc,int current,bool direction){

   if(current == n-2){
        arcs++;
        return;
    }

    // Refix for more than 1 block insertions
    if(direction)   arc[current] = arc[current -1] + h - 1; 
    else arc[current] = arc[current -1] - h + 1;
  
    // If it reaches the n-2 block without failing any rule an arc was successfully made
 
    int cur = arc[current];
    if(cur>max_h) return;
    if(cur == max_h)     buildArc(n,h,max_h,arc,current + 1,DOWN); // Call with DOWN ??
    else{
    buildArc(n,h,max_h,arc,current + 1,UP);
    buildArc(n,h,max_h,arc,current + 1,DOWN);
    }
}

void 


int main() {
 std::ios_base::sync_with_stdio(0);
 std::cin.tie(0);
 int t,n,h,max_h;
 std::cin >> t;

 for(int i=0;i<t;++i){
     std::cin>>n>>h>>max_h;
     for(int j=2;j<n;++j){
        std::vector<uint> arc(j);
        if(j==2) arcs++;
        else{
            arc[0] = 0;
            arc[1] = h; // needs change if second and second to last can have more than 1 block
            arc[j-2] = h;
            arc[j-1] = 0;
            buildArc(n,h,max_h,arc,2,UP);
        }

     }
 }
}