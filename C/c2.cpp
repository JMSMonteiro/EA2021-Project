#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string> 

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
#define pb push_back
#define MAX 100005
#define WS " "
#define LF "\n"
#define DEBUG 1


// C++ implementation of tarjan's algorithm for SCC
// foundat: analogous to time at which the vertex was discovered
// disc: will contain the foundat value of ith vertex(as in input graph)
// low: will contain the lowest vertex(foundat value) reachable from ith vertex(as in input graph)
// onstack: whether the vertex is on the stack st or not
// scc: will contain vectors of strongly connected vertices
// which can be iterated using
// for(auto i:scc){ // here i is a set of strongly connected component
//     for(auto j:i){ 
//         // iterate over the vertices in i
//     }
// }
int foundat=1;
vvi graph,scc;
vi dfs,low; // init disc to -1
bool onstack[MAX]; //init to 0 

void tarjan(int u){
    static std::stack<int> st;

    dfs[u]=low[u]=foundat++;
    st.push(u);
    onstack[u]=true;
    for(auto i:graph[u]){
        if(dfs[i]==-1){
            tarjan(i);
            low[u]=std::min(low[u],low[i]);
        }
        else if(onstack[i])
            low[u]=std::min(low[u],dfs[i]);
    }
    if(dfs[u]==low[u]){
        vi scctem;
        while(1){
            int v=st.top();
            st.pop();onstack[v]=false;
            scctem.pb(v);
            if(u==v)
                break;
        }
        scc.pb(scctem);
    }
}




int main() {
  // Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  // End of Fast(er) I/O

  int testCases;
  int POIs, conns, questions;
  uint startPoint, endPoint, distance;
  int circuits,largest,longest;

  std::cin >> testCases;
  
  for (int i = 0; i < testCases; ++i) {

    std::cin >> POIs >> conns >> questions;
    graph.clear();graph.resize(POIs+1);
    dfs.clear();dfs.resize(POIs+1,-1);
    low.clear();low.resize(POIs+1);
    if(conns == 0){
      for(int c = 0; c< questions;++c){
        std::cout<<"0"<<WS;
      }
      std::cout<<LF;
    }
    for (int j = 0; j < conns; ++j) {
      std::cin >> startPoint >> endPoint >> distance;
      startPoint--;
      endPoint--;
      graph[startPoint][endPoint] = distance;

    }

    if(DEBUG){
      for(auto g: graph){
        for(auto gg: g)
          std::cout<<gg<<WS;
        std::cout<<LF;   
      }
    }


    for(int i= 0;i<POIs;++i){
      if(dfs[i+1] == -1)  tarjan(i);
    }

    circuits = 0;
    largest = 0;
    longest = 0;

    for(auto i:scc){ 
      std::cout<<"Component: ";
      for(auto j: i) {
       std::cout<<j<<WS;
      }
      std::cout<<LF;
      int k = i.size();
      if(k==1) continue;
      else circuits++;
      largest = std::max(largest,k);
    }
    if(circuits == 0) {largest = 0;longest = 0;}
    std::cout<<circuits;
    if(questions >= 2)  std::cout<<WS<<largest;
    if(questions >= 3)  std::cout<<WS<<longest;
    if(questions == 4)  std::cout<<WS<<"kruskal todo";
    std::cout<<LF;
  }
  
  return 0;
}