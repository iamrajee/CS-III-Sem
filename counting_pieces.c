/*
   Program Name: counting_pieces.c
   Program Description: Write a C program which uses BFS to count the number of connected components in a graph. 
			User inputs: Name of the file containing adjacency matrix of the graph
			Generate a dot file for the graph, in which the edges of the BFS tree you trace is shown in a red colour.
   Date: 21/10/17 */

#include<stdio.h>
#include<stdlib.h>

#define MAX 100  

#define initial 1
#define waiting 2
#define visited 3

/* Global varibles */
int count=0;
int n;  
int adj[MAX][MAX], parent[MAX];
int state[MAX]; 
int queue[MAX], front = -1,rear = -1;
char name[20];
int visit[MAX];

/* function to read adjaceny matrix */
int genadj()
{
	FILE *ad;
	int i,j;
	char  type[10], junk, filename[40],ch;

	printf("Enter input filename\n");
	scanf("%s", filename);

	ad=fopen(filename, "r"); //opens the file to read
	
	/* checks whether the input file contains any data or not */
	if (ad == 0)  
	{
		printf("Error in opening the file\n"); //displays error message
		return(1); //returns 1 if input file does not contain any data
	}

	fscanf(ad,"%s %s", name, type); //reads from the input file
	

	fscanf(ad,"%d", &n); //reads from the input file
	fscanf(ad,"%c", &junk); //reads from the input file

	/* nested loop to scan the data from input file */
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			fscanf(ad, "%c", &ch); //reads from the input file
			if(ch=='0')
				adj[i][j]=0;
			else if(ch=='1')
				adj[i][j]=1;
		}
		fscanf(ad,"%c", &junk); //raeds from the input file
	}


	fclose(ad); //closes input file

	return 0; //returns 0 if input file contains data
}

/* function to give initial values to visit and parent array */
void initialize()
{
	int i;
	for(i=0; i<n; i++)
	{
		visit[i]=0;
		parent[i]=-1;
	}
}

/* function to insert a node in the queue */
void insert_queue(int vertex)
{
	if(rear == MAX-1)
		printf("Queue Overflow\n");
	else
	{
		if(front == -1) 
			front = 0;
		rear = rear+1;
		queue[rear] = vertex ;
	}
}

/* function to check if the queue is empty */
int isEmpty_queue()
{
	if(front == -1 || front > rear)
		return 1;
	else
		return 0;
}

/* function to delete a node from the queue */
int delete_queue()
{
	int delete_item;
	if(front == -1 || front > rear)
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	
	delete_item = queue[front];
	front = front+1;
	return delete_item;
}

/* function for breadth first search */
void BFS(int v)
{
	int i;
	
	insert_queue(v);
	state[v] = waiting;
	
	while(!isEmpty_queue())
	{
		v = delete_queue();
		state[v] = visited;
		for(i=0; i<n; i++)
		{
			if(adj[v][i] == 1 && state[i] == initial) 
			{
				visit[i]=1;
				parent[i]=v;
				insert_queue(i);
				state[i] = waiting;
			}
		}
	}
}

/* function for breadth first traversal */
void BF_Traversal()
{
	int i;
	for(i=0; i<n; i++) 
		state[i] = initial;
	for(i=0; i<n; i++)
	{
		if(visit[i]==0)
		{
			BFS(i);
			count++;
		}
	}
}

/* function to generate dot of the graph */
void gendot()
{
	FILE *dot;
	char filename[40];
	int i,j,chk;

	printf("Enter output filename\n");
	scanf("%s", filename);

	dot=fopen(filename, "w"); //opens the file to write

	fprintf(dot,"graph %s{\n", name); //writes to the output file

	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(adj[i][j]==1)
			{
				adj[j][i]=0;
				if(parent[i]==j || parent[j]==i)
					fprintf(dot,"%d -- %d [color=red] ;\n",i,j); //writes to the output file
				else
					fprintf(dot,"%d -- %d ;\n",i,j); //writes to the output file
			}
		}
	}
	fprintf(dot,"}"); //writes to the output file

	fclose(dot); //closes output file
}

int main()
{
	int rt; // rt is a integer variable
	rt=genadj(); //calls the function genadj
	initialize(); //calls the function initialize
	BF_Traversal(); //calls the function BF_Traversal
	gendot(); //calls the function gendot
	printf("Number of connected components = %d\n", count);
	return 0;
}
