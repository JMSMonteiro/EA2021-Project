#include <cstdio>
#include <iostream>
#include <vector>


void a(std::vector<int> &tab,int rows,int columns,int start){
    int leftmost = 0;
    int line = 1;
    int col = 0;
        for(int i = start; i < rows*columns;++i){
            std::cout<<"Line: "<<line<<" Col: "<<col<<" Val:"<<tab[i]<<"\n";
            leftmost++;
            if(tab[i+1] == 0){
                if(tab[i + columns] == 0){
                    i = i + columns ; 
                }
                else i = i + columns - leftmost;
                leftmost = 0;
                col = 0;
                line++;
                if(tab[i+1] == 0){
                    return;
                }
            }
            col++;
        }
}



int main() {
    //Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    //End of Fast(er) I/O
    std::vector<int> tab = {1,0,0,0,0, 
                            0,1,0,0,0, 
                            0,1,1,0,0, 
                            0,1,2,1,0, 
                            0,1,3,3,1, 
                            0,0,0,0,0};
    int columns = 5;
    int rows = 6;
    std::cout<<"Columns + 1 start\n";
    a(tab,rows,columns,columns + 1); // starts on x=1 y=1
    std::cout<<"0 start\n";
    a(tab,rows,columns,0); // starts on i = 0

}