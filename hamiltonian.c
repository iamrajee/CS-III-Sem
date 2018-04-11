#include <stdio.h>
#include "hamiltonian.h"
#include <stdlib.h>
#define fo(i,a,b) for(i=a;i<b;i++)
//checks whether a given vertex can be inserted at a given postion in the HAM path
int check(int a[][100],int vertex,int size,int ham[],int pos){
    
    int i;
    //first check if its adjacent to the prev position
    if(pos>=1 && a[vertex][ ham[pos-1] ] ==0){
        //0 for false
        return 0;
    }
    
    else{
        //then check if it is already in the path
        fo(i,0,pos){
            if(ham[i]==vertex){
                return 0;
            }
        }
        //if reaches here then its OK
        return 1;
    }
    
}

int make_ham_cycle(int a[][100],int size,int ham[],int pos){
    
    
    int i,solution;
    //base case if already hamiltonian cycle is formed
    if(pos==size){
        if(a[ham[0]][ham[pos-1]]==1){
            //found
            return 1;
        }
        else{
            return 0;
        }

    }
    fo(i,1,size){
        //if we can put i in the path
        if(check(a,i,size,ham,pos)==1){
             //then put it
            ham[pos]=i;
                
            //..and dig deeper from here
            solution=make_ham_cycle(a,size,ham,pos+1);
               
            //..now if we made a mistake 
            if(solution==0){
                //..then undo it
                ham[pos]=-1;
            }
            else{
                //otherwise signal that solution exists
                return 1;
            }
        }
    }
    //if reaches here then no for no i solution exists 
    //so return 0 to backtrack to the position where a faulty vertex was inserted
    return 0;
}
//function to print ham cycle edges in red
void print_ham_path(int ham[],int size,int a[][100],FILE *foo){
    int i;
    fo(i,0,size-1){
        fprintf(foo,"%d--%d[color=red]\n",ham[i],ham[i+1]);
        a[ham[i]][ham[i+1]]=0;
        a[ham[i+1]][ham[i]]=0;
    }
    fprintf(foo,"0--%d[color=red]\n",ham[size-1]);
    return ;
}



