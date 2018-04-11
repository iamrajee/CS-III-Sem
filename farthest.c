/*
Program Author -- Arko Sharma
Date           -  03/10/2017

Topic          - Graphs( Experiment 1 Problem 2)

Function       - Finds the diameter of a connected graph and highlights the diametric path in a dot file
*/




//in this program the adjacency matrix is used to keep track of neighbours of a vertex !



#include <stdio.h>
#include <stdlib.h>
#define fo(i,a,b) for(int i=a;i<b;i++)
//vertices have 3 attributes , viz, color,value,distance
typedef struct vertex {
    
    int value;               // the label of the vertex
    char color;              // can be White, Gray ,Black
    int  dist;               // distance from source in BFS
    int par;                 // the parent in BFS tree
}ver;
typedef struct vertex* verp;

typedef struct node
{
	//nodes for the circular queue
	int data;
	struct node *next;
}nod;
typedef  nod *nodp;
typedef struct queue
{
	nodp front;
	nodp rear;
}qu;
typedef qu *queue;// pointers to struct "queue" will be called queue


queue newQueue(){
	//creates a new queue and returns its reference
	queue q=(queue)malloc(sizeof(qu));
	q->front=NULL;
	q->rear=NULL;
	return q;
}

int queueIsEmpty(queue q){
	//returns 1 if empty and 0 if not
	
	// doesn't change the queue so no need of pointer, but 
	//pass by reference saves memory as new structure not created
	if(q->front==NULL)
		return 1;
	else
		return 0;
}
int queueSize(queue q){
    //returns no of elements in the queue
	
	// doesn't change the queue so no need of pointer, but 
	//pass by reference saves memory as new structure not created
	
	
	int siz=0;
	nodp start=q->front;
	while(start!=NULL){
		siz++;
		if(start == q->rear)
			break;
		else
			start=start->next;
	}
	return siz;
}
void enQueue(queue q,int x){
	//takes a queue reference and adds x as a new node to it
	//note q is circular
    nodp np=(nodp)malloc(sizeof(nod));
    np->data=x;
    //fifo so insert at rear
    if(queueIsEmpty(q)==1){
    	//if empty
    	q->front=np;
    }
    else{
    	q->rear->next=np;
    }
    q->rear=np;
    q->rear->next=q->front;
    return;
}
int deQueue(queue q){
    
	//takes reference of a queue, deletes front node, returns its "data"
	
	//since it changes the queue so it takes a pointer to the queue
	if(queueIsEmpty(q)==1)
	{
     
      printf("fatal error! queue is empty!\n");
	  return -1111;
	}

	int temp=q->front->data;//for returning
	nodp temp1=q->front;  //for freeing

	if(queueSize(q)==1){
		//only 1 node
	    q->front=NULL;
	    q->rear=NULL;
	}
	else{
		//more than 1 nodes
		q->front=q->front->next;
		q->rear->next=q->front;
	}
	free(temp1);
	return temp;
}
 void queueFront(queue q){
	//prints front of the queue
	
	
	// doesn't change the queue so no need of pointer, but 
	//pass by reference saves memory as new structure not created
	
	
	if(queueIsEmpty(q)){
		printf("queue is empty!!\n\n");
	}
	else
		printf("%d\n",q->front->data );
	return ;
}
void free_memory(queue q){
    while(queueIsEmpty(q)!=1){
		int a=deQueue(q);
	}
	return ;
}

/*function to fill in required "value" attributes as vertex-labels*/
void mark_labels(verp v,int size){
    
    int i;
    fo(i,0,size){
        v[i].value=i;  //here labels are the indices themselves
    }
    
}




/*BFS function*/
/* the matrix "a " contains the adjacency matrix whereas the array v is the array of attributes  of vertices*/

void BFS(int a[][100],int source,int size,FILE *foo,int visited[],verp v){
    
    int i,u,j,neighbours;
    
    //note in initialising the attributes it is assumed that the graph is connected
    // so it is important not to use these attributes to determine the connectivity of the graph
    fo(i,0,size){


        
        //initialise attributes of vertices except source
        if(i!=source){
            v[i].color='W';                    // White => unexplored
            v[i].dist= 100000;                 //max distance assumed 100000
            v[i].par=-1;
        }
    }
    // now for source
    // gray => not explored completely
    v[source].color='G';        
    v[source].dist=0;
    v[source].par=-1;

    visited[source]=1;
    qu que=*(newQueue());
    //push the source in queue ( in case labels of vertices are not indices , use v[source].value instead of source )
    enQueue(&que,source);        
    
    // while queue is not empty
    while(queueIsEmpty(&que)!=1){
        u=deQueue(&que);
        neighbours=0;
        //for each j adjacent to u
        fo(j,0,size){
            
            if(a[u][j]==1){
                //count neighbours
                neighbours++;
                //if j is unvisited
                if(visited[j]==0){
                    visited[j]=1;
                    enQueue(&que,j);
                    v[j].dist=v[u].dist+1;
                    v[j].par=u;
                    v[j].color='G';
                }
            }
            
            
        }
        v[u].color='B';
        visited[u]=1;
    }
    //finished processing all vertices reachable from source.Now queue is empty
    return ;
 }



/*function to write edges in dot file depending on values of color array c */
void write_edges(int a_matrix[][100],FILE *foo,int color[][100],int size){
    int i,j,neighbours=0;
    fo(i,0,size){
        neighbours=0;
        fo(j,i,size){
            if(a_matrix[i][j]==1){
                //colored ones
                if(color[i][j]==1){
                    fprintf(foo,"\t%d--%d\t[color=red]\n",i,j);
                    
                }
                //non colored ones
                else{
                    fprintf(foo,"\t%d--%d\t\n",i,j);
                }
            }
        }
        //isolated ones
        if(neighbours==0){
            fprintf(foo,"%d\n",i);
        }
    }
}

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



/*functon to copy values of a matrix in another*/
void get_copy(int b[][100],int a[][100]){
    int i,j;
    fo(i,0,100){
        fo(j,0,100){
            a[i][j]=b[i][j];
        }
    }
    return;
}


/*function to fill all distances in a connected graph using Floyd Warshall algorithm*/
void fill_distances(int distance[][100],int size){
    int i,j,k;
    fo(k,0,size){
        fo(i,0,size){
            fo(j,0,size){
                if(distance[i][j] > distance[i][k] + distance[k][j]){
                    
                    distance[i][j]=distance[i][k]+distance[k][j];
                    distance[j][i]=distance[i][k]+distance[k][j];
                }
            }
        }
    }
    return;
}
/*function to color a shortest path red in the dot file and turn the concerned edges  off in   AM*/
void write_del_shortest_edges(int a[][100],int size,verp v,int source,int dest,FILE *foo){
    if(source==dest){
        return ;
    }
    else{
        
        fprintf(foo,"\t%d--%d[color=red];\n",dest,v[dest].par);
        //turn off this edge
        a[dest][v[dest].par]=0;
        a[v[dest].par][dest]=0;
        //recurse for parents
        write_del_shortest_edges(a,size,v,source,v[dest].par,foo);
        
    }
    
}
/*function to print remaining edges in dot file (assumes the beginning syntax graph g_name{ is already printed/*
/*  does not close the dot function with } */
void write_remaining_edges(int a[][100],int size,FILE *foo){
    int i,j,count;
    fo(i,0,size){
        count=0;
        //for upper tr of AM , start j from i 
        fo(j,i,size){   
            if(a[i][j]==1){
                fprintf(foo,"\t%d--%d;\n",i,j);
                count++;
            }
        }
        //for isolated vertices : 
        if(count ==0){
            fprintf(foo,"\t%d;\n",i);
        }
    }
    return;
    
}


/*to create a dot file with a highlighted shortest path bw source and dest*/
void red_marked_shortest_path(int a[][100],int size, verp v,int source,int dest, FILE *foo){
    
    
    //open the module
    fprintf(foo,"graph diameter{\n");   

    //first print a shortest path in red and delete these edges from adjacency matrix
    write_del_shortest_edges(a,size,v,source,dest,foo); 

    // then print the remaining edges into the file
    write_remaining_edges(a,size,foo);             

    // cap off the file with }
    fprintf(foo,"}");                        
    return;
    
    
}

int main() {
    char file_name[100],gr_name[100],id[3],dot_fil_name[100];
    int size,choice=1,x,y,d=0,numConnectedComp=0,max_index1=0,max_index2=0,i,j;
    ver v[100];
    int a[100][100],b[100][100],c[100][100],visited[100],distance[100][100];//default max assumed to be 100
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
        printf("Enter the name of the dot-file to store the graph with highlighted diametric path \n");
        scanf(" %[^\n]s",dot_fil_name);
        foo=fopen(dot_fil_name,"w");
        if(foo==NULL){
            printf("error in opening file !! Exiting Program !! \n");
            return 0;
        }
        
        if(id[1]=='M'){      
           
           
           
           
            //then populate the adj matrix  "b" 
            populate_am(b,size,fp); 
            mark_labels(v,size);
           
            //do operations on the adj matrix in here
        
        
            //make a copy of the original AM "b"in "a"  
            get_copy(b,a);        
        
        
           /*initialisation*/
           fo(i,0,size){
                visited[i]=0;
                distance[i][i]=0;
                fo(j,0,size){
                    
                    //the distance bw adjacent vertices will be 1
                    if(b[i][j]==1){
                        distance[i][j]=(i==j)? 0:1;
                        distance[j][i]=(i==j)? 0:1;
                    }
                    else if(b[i][j]==0){
                    //assume INFINITE DISTANCE 1000000
                        distance[i][j]=(i==j)?0:1000000;
                        
                        distance[j][i]=(i==j)? 0:1000000;
                    }
                }
            }
            
        
        
        
                
            //if there is atleast one vertex
            if(size>=1){
                //then run BFS on the first vertex for initialising the colours of all vertices
                BFS(a,0,size,foo,visited,v);
                numConnectedComp=1;
                visited[0]=1;
                foo=fopen(dot_fil_name,"w");
                fprintf(foo,"graph bfs_trees{\n");
                
            
                //now " for " all other vertices;
                fo(i,1,size){
                    //if  a vertex is not visited then it is a new connected component
                
                    if(visited[i]==0){
                        //so increment conn.comp counter
                        numConnectedComp++;
                        
                        //and BFS it
                        BFS(a,i,size,foo,visited,v);
                    
                    
                    }
                }
                //if theres only one connected component
                if(numConnectedComp==1){
                    
                    fill_distances(distance,size);
                    fo(i,0,size){
                        fo(j,0,size){
                          
                            //store the indices of the endpoints of the diametric path 
                            if(distance[i][j] > distance[max_index1][max_index2]){
                                max_index1=i;
                                max_index2=j;
                                
                            }
                        }
                       
                    }
                    //print the dot file with diametric path red
                    //here the shortest path between max_index1 and 2 is the diametric path
                    fo(i,0,size){
                        visited[i]=0;
                    }
                    visited[max_index1]=1;
                    BFS(a,max_index1,size,foo,visited,v);
                    red_marked_shortest_path(a,size,v,max_index1,max_index2,foo);
                    
                    printf("The diameter length is %d\n\n",distance[max_index2][max_index1]);
                }
                else{
                    printf("The graph is disconnected\n\n");
                }
                
                
            }
            //if size was 0
            else{
                printf("The diameter length is  0\n\n");
                
            }
        }
        fclose(foo);
        fclose(fp);
        return 0;
}
