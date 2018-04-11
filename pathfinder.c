/*
Date           -  03/10/2017

Topic          - Graphs( Experiment 1 Problem 2)

Function       - Looking for a path between user entered edges using BFS and prints a shortest path between them if one exists
                 Also it creates a dot file of desired name to highlight the particular path.
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
	//nodes for the circular linked list
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



/*BFS function*/
/* the matrix "a " contains the adjacency matrix whereas the array v is the array of attributes  */

void BFS(int a[][100],int source,int size,verp v){
    
    int i,u,j;
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

    qu que=*(newQueue());
    enQueue(&que,source);        //we are only pushing the indices (here labels of vertices)
    
    // while queue is not empty
    while(queueIsEmpty(&que)!=1){
        u=deQueue(&que);
        //for each adjacent to u
        fo(j,0,size){
            if(a[u][j]==1){
                //if unvisited
                if(v[j].color=='W'){
                    v[j].dist=v[u].dist+1;
                    v[j].par=u;
                    v[j].color='G';
                    enQueue(&que, j);
                }
            }
            
            
        }
        v[u].color='B'; //finished exploring "u"
    }
    //finished exploring source since queue is empty
    return ;
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

/*function to fill in required "value" attributes as vertex-labels*/
void mark_labels(verp v,int size){
    
    int i;
    fo(i,0,size){
        v[i].value=i;  //here labels are the indices themselves
    }
    
}

/* function to use bfs attributes to print a shortest path from a source to a destination */
void print_shortest_path(verp v,int source,int dest){
    
    if(source == dest){
        printf(" %d ",v[dest].value);
        return ;
    }
    else{
        
        printf(" %d ",v[dest].value);
        print_shortest_path(v,source,v[dest].par);
    }
    return;
}
/* function to use bfs attributes to get the distance from a source to a destination */
int get_dist(verp v,int source,int dest,int c){
    
    if(source == dest){
        return c;
    }
    else{
        
        c++;
        get_dist(v,source,v[dest].par,c);
        
    }
    
}
/* to print the adjacency matrix*/
void print_am(int a[][100],int size){
    
    int i,j;
     fo(i,0,size){
         fo(j,0,size){
             printf("%d ",a[i][j]);
         }
         printf("\n");
     }
    return;
}
/*function to turn color path edges red and turn them  off*/
void am_to_dot_red(int a[][100],int size,verp v,int source,int dest,FILE *foo){
    if(source==dest){
        return ;
    }
    else{
        
        fprintf(foo,"%d--%d [color=red];\n",dest,v[dest].par);
        a[dest][v[dest].par]=0;
        a[v[dest].par][dest]=0;
        am_to_dot_red(a,size,v,source,v[dest].par,foo);
        
    }
    
}
/*function to print remaining edges in dot file */
void am_to_dot_black(int a[][100],int size,FILE *foo){
    int i,j,count;
    fo(i,0,size){
        count=0;
        fo(j,0,size){
            if(i<=j && a[i][j]==1){
                fprintf(foo,"%d--%d;\n",i,j);
                count++;
            }
        }
        if(count ==0){
            fprintf(foo,"%d;\n",i);
        }
    }
    return;
    
}


/*to create a dot file with a highlighted shortest path bw source and dest*/
void am_to_dot_path(int a[][100],int size, verp v,int source,int dest, FILE *foo){
    
    
    
    fprintf(foo,"graph shortest_path{\n");   
    am_to_dot_red(a,size,v,source,dest,foo); //first make the shortest path edges red in color and turn these edges off in the adjacency matrix
    am_to_dot_black(a,size,foo);                 // then print the remaining edges into the file
    fprintf(foo,"}");                        // cap off the file with }
    return;
    
    
}




int main() {
    char file_name[100],gr_name[100],id[3],dot_fil_name[100];
    int size,choice=1,x,y,d=0;
    
    int a[100][100];//default max assumed to be 100 vertices!
    ver v[100];
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
    fscanf(fp," %[^\n]s",id);     // id contains either AM or AL 
    fscanf(fp,"%d",&size);   

    
    if(id[1]=='M'){     // if the id is AM 
    
        populate_am(a,size,fp); //then populate the adj matrix
        mark_labels(v,size);
//      print_am(a,size);       //to see the populated am
            

    //do operations on the adj matrix in here
        while(choice==1){
            
            printf("Enter the 2 vertices (should be ZERO INDEXED ! ) to be checked for connectivity \n\n");
            scanf("%d %d",&x,&y);
            BFS(a,x,size,v);
            if(v[y].color == 'W')     // if the color is WHITE , then the vertex y is not visited, so there is no path
               printf(" NOT CONNECTED  \n");
            else{ 
               printf(" CONNECTED   (a shortest path is shown below )  \n\n");
               
               print_shortest_path(v,x,y);
               d=get_dist(v,x,y,0); //0 => for initialisation
               printf("\nthe distance between them is %d \n\n",d);
               
               printf("Enter the name of the dot-file to store the graph with highlighted path\n");
               scanf(" %[^\n]s",dot_fil_name);
               foo=fopen(dot_fil_name,"w");
               if(foo==NULL){
                   printf("error in opening file !! Exiting Program !! \n");
                   return 0;
               }
               am_to_dot_path(a,size,v,x,y,foo);
               fclose(foo);
            }
            printf("For checking more vertices , enter 1 else enter 0 to exit\n\n");
            scanf("%d",&choice);
        }
    }
    fclose(fp);
    return 0;
}
  


