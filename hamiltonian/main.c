/*
Date           -  17/10/2017

Topic          - Graphs( Experiment 2 Problem 1)

Function       - Finds a HAMILTONIAN cycle and displays it in a dot file
*/


//in this program the adjacency matrix is used to keep track of neighbours of a vertex !



#include <stdio.h>
#include <stdlib.h>
#include "graph_lib.h"
#include "hamiltonian.h"
#define fo(i,a,b) for(int i=a;i<b;i++)
#define pi(n) printf(" %d ",n);





int main() {
    char file_name[100],gr_name[100],id[3],dot_fil[30];
    
    int size,x,y,d=0,numConnectedComp=0,i,j,trigger,eul=1,ret=0,is_poss;
    int a[100][100],b[100][100],degree[100],visited[100],ham[100];//default max assumed to be 100
    FILE *fp=NULL,*foo=NULL;
    
    

        
        printf("Enter the name of the file containing the graph\n(default max assumed to be 100 vertices!)\n\n");
        scanf(" %[^\n]s",file_name);
        fp=fopen(file_name,"r");
        if(fp==NULL){
            printf("Error in opening file \n\nExiting program \n\n");            
            return 0;
        }
        //reading from the user-entered file
        
        
    
      
        fscanf(fp," %[^\n]s",gr_name);
        // id contains either AM or AL 
        fscanf(fp," %[^\n]s",id);     
        fscanf(fp,"%d",&size);   

        // if the id is AM
        printf("Enter the name of the file in which HAMILTONIAN cycle is to be printed \n");
        scanf(" %[^\n]s",dot_fil);
        foo=fopen(dot_fil,"w");
        if(foo==NULL){
            printf("ERROR in opening file\n\n");
            return 1;
        }
        if(id[1]=='M'){      
           
            //then populate the adj matrix  "b" 
            populate_am(b,size,fp); 
            
           
            //do operations on the adj matrix in here
            ham[0]=0;
            fo(i,1,size){
                //initially
                ham[i]=-1;
            }
            //start making cycle from position 1 as 0 already filled
            is_poss=make_ham_cycle(b,size,ham,1);
            if(is_poss==0){
                printf("NO HAMILTONIAN cycle exists\n");
                return 0;
                
            }
            else{
                fprintf(foo,"graph ham{\n");
                print_ham_path(ham,size,b,foo);
                am_to_dot(b,size,foo);
            }
       }

        
        fclose(fp);
        return 0;
}
