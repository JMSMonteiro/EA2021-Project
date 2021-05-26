#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string> 


#define WS " "
#define LF "\n"
#define DEBUG 0
using uint = unsigned int;
using vec = std::vector<int>;
using matrix =   std::vector<vec>;     
using p = std::pair<int>;
using pp = std::pair<int,p>;
using pv = std::vector<pp>;

// Kruskal

void setK(vec v,vec &parent, vec &rank){
  
  for(int i=0;i<v.size();++i){
      parent[i] = i; 
      rank[i] = 0;
      i++;
  }

}

int findK(int i,vec &parent) {

  if (parent[i] != i) parent[i] = findK(parent[i],parent);
  
  return parent[i];
}


void linkK(int u,int v,vec &parent , vec &rank){

  if(rank[u] > rank[v]) parent[v] = u;
  else parent[u] = v;
  if(rank[u] > rank[v]) rank[v]++;

}



void unionK(int u, int v,vec &parent , vec &rank) {

  linkK(findK(u,parent),findK(v,parent),parent,rank);

}

bool PCompare (pp a, pp b)
{
    return a.first < b.first;
}




void kruskal(const matrix graph,vec circuit,vec &parent,vec &rank ) {
    pv weights;
    for(int c= 0;c<circuit.size;++c){
        setK(circuit[c],parent,rank);
        for(int k = 0;k<c;++k){
            weights.push_back(std::make_pair(graph[circuit[c]][circuit[k]],std::make_pair(circuit[c],circuit[k])));
        }
        
    }
    std::sort(weights.start(),weights.end(),PCompare());
    for(auto w: weights){
      
    }
}



//Tarjan
void tarjan(const int v,const matrix graph,vec &dfs,vec &low,matrix &scc,vec &stacked,uint &index){
    static std::stack<int> s;
    dfs[v]=low[v]=index++;
    s.push(v);
    stacked[v]=true;
    for(int i= 0;i<graph[v].size();i++){
        if( graph[v][i] != 0){
        if(dfs[i]==-1){
            tarjan(i,graph,dfs,low,scc,stacked,index);
            low[v]=std::min(low[v],low[i]);
        }
        else if(stacked[i] == true)
            low[v]=std::min(low[v],dfs[i]);
        }
    }
    if(dfs[v]==low[v]){
        vec temp;
        int u;
        do{
            u=s.top();
            s.pop();
            stacked[u]=false;
            temp.push_back(u);
        }while(v!= u);
        scc.push_back(temp);
    }
}




int main() {
  // Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  // End of Fast(er) I/O

  int testCases;
  int POIs, conns, questions;
  uint startPoint, endPoint, distance,index;;
  int circuits,largest,longest;

  std::cin >> testCases;
  
  for (int i = 0; i < testCases; ++i) {

    std::cin >> POIs >> conns >> questions;
    matrix graph(POIs,vec(POIs,0));
    matrix scc;
    vec dfs(POIs,-1);
    vec low(POIs);
    vec parent(POIs);
    vec rank(POIs);

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


    vec stacked(POIs,0);
    index = 0;

    for(int i= 0;i<POIs;++i){
      if(dfs[i] == -1)  tarjan(i,graph,dfs,low,scc,stacked,index);
    }

    if(DEBUG){
      std::cout<<LF<<LF;
      std::cout<<"DFS: ";  
      for(auto d: dfs)  std::cout<<d<<WS;
      std::cout<<LF<<LF;
      std::cout<<"LOW: ";  
      for(auto l: low) std::cout<<l<<WS;
      std::cout<<LF<<LF;
    }

    circuits = 0;
    largest = 0;
    longest = 0;
    for(auto i:scc){ 
      for(auto j: i) {
      }
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