#include <stdio.h>
#include <stdlib.h>
#include "graph_lib.h"
#define fo(i,a,b) for(i=a;i<b;i++)
/*function to read an adjacency matrix into a given array*/
/*takes array,size and file pointer as parameters*/
void populate_am(int a[][100],int size,FILE *fp){
     
     int i,j;
     fo(i,0,size){
         fo(j,0,size){
             fscanf(fp,"%1d",&a[i][j]);
         }
     }
     return;
}

/*function to generate the dot file in the given pointer from AM*/
void am_to_dot(int a[][100],int size,FILE *foo){
    
    
    int i,j,count=0;
    fo(i,0,size){
        count=0;
        fo(j,0,size){
            
            
            // if there is an edge ,, only for upper triangular matrix elememts: 
            if(i<=j && a[i][j]==1) {         
                   
                       
                   fprintf(foo,"\t%d --%d;\n",i,j);
                   count++;
                
            }
            
        }
        if(count==0){
            
            //print isolated vertices
            
            fprintf(foo,"%d",i);             
        }
        //at the end go to new line after semicolon
        fprintf(foo,"\n");
    }
    fprintf(foo,"}");
    return;
    
}


