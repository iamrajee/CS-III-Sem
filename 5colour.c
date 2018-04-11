/*
Module: Graphs
Exercise 7.
Programme Description: Enhance 6colour.c to a 5-colouring algorithm using Kempe/Haewood idea. 
Date: 10/10/2017
*/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#define LEN 51

//defining structures for queue and its nodes
struct Node
{
	int val;
	struct Node *ptr;
};

//defining structure for circular linked list
struct Queue
{
	struct Node *front;
	struct Node *rear;
};

typedef struct Node* node;
typedef struct Queue* qu;

//function to create a new queue
qu newQu()
{
	qu temp=(qu)malloc(sizeof(struct Queue));
	if(!temp)
		return NULL;
	else
	{
		temp->front=NULL;
		temp->rear=NULL;
		return temp;
	}
}

//function for enquing
int enQu(qu q,int data)
{
	node temp=(node)malloc(sizeof(struct Node));
	if(!q || !temp)
		return 0;
	else
	{
		temp->val=data;
		temp->ptr=NULL;
		if(q->rear)
			q->rear->ptr=temp;
		q->rear=temp;
		if(!q->front)
		{
			q->front=temp;
		}
		return 1;
	}
}

//function for dequing
int deQu(qu q,int* data)
{
	if(!q || !q->front)
		return 0;
	else
	{
		node temp=q->front;
		q->front=q->front->ptr;
		if(!q->front)
			q->rear=NULL;
		*data=temp->val;
		free(temp);
		return 1;
	}
}

//function to check if the queue is empty
int isEmpty(qu q)
{
	if(!q->front)
		return 1;
	else 
		return 0;
}

//function to delete a queue
void delQu(qu q)
{
	int temp;
	while(deQu(q,&temp));
	free(q);
	return;
}

//function for breadth first search to check whether 'x' and 'y' are connected in the graph
int BFS(int mat[][LEN],int size,int x,int y)
{
	int visited[size],temp,i;
	for(i=0;i<size;i++)			//initialising visited[] array. It keeps track of whether a node is visited or not
		visited[i]=0;
	qu q=newQu();				//creating a new queue
	if(!q)
		return -1;
	else
	{
		if(!enQu(q,x))			//enquing x in the queue
		{
			delQu(q);
			return -1;
		}
		visited[x]=1;			//marking x as visited
		while(!isEmpty(q))	
		{
			if(!deQu(q,&temp))	//deQueue a node from the queue
			{
				delQu(q);
				return -1;
			}
			if(temp==y)			//if the node matches with y-the other node, then x and y are connected
			{
				delQu(q);
				return 1;
			}
			else
			{
				for(i=0;i<size;i++)
					if(mat[temp][i] && !visited[i])		//if a node is not visited and is adjacent to temp, mark it visited and enQueue it in the queue
					{
						visited[i]=1;
						if(!enQu(q,i))
						{
							delQu(q);
							return -1;
						}
					}
			}
		}
		delQu(q);
		return 0;
	}	
}	

//function to read a matrix from a file pointed to by filepointer-'ptr'		
int readMat(FILE *ptr, int mat[][LEN], int *size)
{
	if(!ptr)
		return INT_MIN;
	else
	{
		char str[LEN],c;
		int i,j;
		fscanf(ptr," %s",str);
		fscanf(ptr," %s",str);
		fscanf(ptr,"%d",size);
		for(i=0;i<(*size);i++)
			for(j=0;j<(*size);j++)
			{
				fscanf(ptr," %c",&c);
				mat[i][j]=c-'0';
			}
		return 1;
	}
}

//function to check if a graph is empty
int isEmptyGraph(int mat[][LEN],int size)
{
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			if(mat[i][j]==1)
				return 0;
	return 1;
}

//fuction to generate a subgraph of a graph having edges incident only on those vertices which has been coloured by either 'col1' or 'col2'
void genSubgraph(int mat[][LEN], int copy[][LEN], int size, int colour[], int col1, int col2)
{
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
		{
			if((colour[i]==col1 || colour[i]==col2) && (colour[j]==col1 || colour[j]==col2) && (mat[i][j]))
				copy[i][j]=1;
			else
				copy[i][j]=0;
		}
	return;
}

//recursive function to create a degenerate list of vertices of the graph
void createDegnerateList(int mat[][LEN],int list[], int size, int cnt)
{
	if(size==cnt)
		return ;
	else
	{
		int min_deg=INT_MAX,min_deg_node,count,check,i,j;
		for(i=0;i<size;i++)				//counting the degrees of all vertices to find vertex with lowest degree
		{
			count=0;
			check=1;
			for(j=0;j<size;j++)
			{
				if(mat[i][j]==1)
					count++;
				else if(mat[i][j]==-1)
				{
					check=0;
					break;
				}
			}
			if(check)
			{
				if(count<min_deg)
				{
					min_deg=count;
					min_deg_node=i;
				}
			}
		}
		for(j=0;j<size;j++)								//deleting the vertex from the graph and its edges which is added to the degeneracy list
		{
			mat[min_deg_node][j]=-1;
			mat[j][min_deg_node]=0;
		}
		list[size-cnt-1]=min_deg_node;					//adding the node to the degenerate list
		createDegnerateList(mat,list,size,cnt+1);		//recursive calling to create degenrate list the on smaller subgraph
		return;
	}
}

//function to make all elements of an array equal to INT_MIN
void clearMat(int mat[], int size)
{
	int i;
	for(i=0;i<size;i++)
		mat[i]=INT_MIN;
	return ;
}

//function to recolour vertices as is required during 5-colouring of a planar graph using Kemp-Heawood idea
int recolour(int mat[][LEN], int size, int x, int colour[], int col1, int col2)
{
	int visited[size],temp,i;
	for(i=0;i<size;i++)	//initialising visited[] array. It keeps track of whether a node is visited or not
		visited[i]=0;
	qu q=newQu();		//creating a new queue
	if(!q)
		return -1;
	else
	{
		if(!enQu(q,x))		//enquing x in the queue
		{
			delQu(q);
			return -1;
		}
		visited[x]=1;		//marking x as visited
		colour[x]=col2;		//change colour of starting vertex
		while(!isEmpty(q))	
		{
			if(!deQu(q,&temp))	//deQueue a node from the queue
			{
				delQu(q);
				return -1;
			}
			else
			{
				for(i=0;i<size;i++)
					if(mat[temp][i] && !visited[i])		//if a node is not visited and is adjacent to temp, mark it visited and enQueue it in the queue
					{
						visited[i]=1;
						if(colour[i]==col1)				//change the vertex colour
							colour[i]=col2;
						else
							colour[i]=col1;
						if(!enQu(q,i))
						{
							delQu(q);
							return -1;
						}
					}
			}
		}
		delQu(q);
		return 0;
	}
}

//function to colour the graph using 6-colours
void clrGraph(int mat[][LEN], int size, int deg_list[], int colour[])
{
	int i,j,k,l,used[5],neigh[5],copy[LEN][LEN],check;
	for(i=0;i<size;i++)
		colour[i]=INT_MIN;
	for(i=0;i<size;i++)
	{
		for(j=0;j<5;j++)
			used[j]=0;
		for(j=0,k=0;j<size;j++)				//checking which colours are used by currently coloured vertices adjacent to the current vertex to be coloured
			if((mat[j][deg_list[i]]) && (colour[j]!=INT_MIN))
			{
				used[colour[j]]=1;
				neigh[k++]=j;
			}
		for(j=0;j<5;j++)					//assigning the unused colour,if any of 5-colours, to the current vertex to be coloured 
			if(!used[j])
			{
				colour[deg_list[i]]=j;
				break;
			}
		if(j==5)							//if no colour is currently left,use Kemp-Heawood idea
		{
			check=1;
			for(l=0;(l<4)&&check;l++)
				for(k=l+1;k<5;k++)
				{
					genSubgraph(mat,copy,size,colour,colour[neigh[l]],colour[neigh[k]]);
					if(!BFS(copy,size,neigh[l],neigh[k]))
					{
						colour[deg_list[i]]=colour[neigh[l]];
						recolour(copy,size,neigh[l],colour,colour[neigh[l]],colour[neigh[k]]);
						check=0;						
					}
				}
		}
	}
	return;
}		

//function to copy second matrix into the first matrix		
void copyMat(int a[][LEN], int b[][LEN], int size)
{
	int	i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			b[i][j]=a[i][j];
	return;
}

//function to write the *.dot file corresponding adjacency matrix and vertex colours
int printDot(FILE *fout, int adjMat[][LEN], int size, int colour[])
{
	if(!fout)
		return INT_MIN;
	else
	{
		char *clr[]={"blue","red","green","orange","yellow","brown","cyan","gold"};
		int i,j;
		fprintf(fout,"graph %s{\n","grph");
		for(i=0;i<size;i++)
			fprintf(fout,"%d [color=%s, style=filled];\n",i,clr[colour[i]]);
		for(i=0;i<size;i++)
			for(j=i;j<size;j++)
				if(adjMat[i][j])
					fprintf(fout,"%d -- %d;\n",i,j);
		fprintf(fout,"}\n");
		return 1;
	}
}

int main()
{
	char fname[LEN];
	int size,adjMat[LEN][LEN],copy[LEN][LEN],deg_list[LEN],colour[LEN],i,col1,col2;
	printf("Enter the file name:");				//taking the filename
	scanf("%s",fname);			
	FILE *fin=fopen(fname,"r");			
	if(readMat(fin,adjMat,&size)==INT_MIN)							//reading the matrix and checking if there is no error
	{
		printf("Error opening file.\nExiting..........\n");
		return 0;
	}
	fclose(fin);
	copyMat(adjMat,copy,size);										//copying the adjacency matrix into a new matrix
	createDegnerateList(copy,deg_list,size,0);						//creating degenerate list of vertices
	clrGraph(adjMat,size,deg_list,colour);							//colouring vertices based on the degnerate list
	printf("Enter the name of the output *.dot file:");				//writing the output in *.dot file
	scanf("%s",fname);
	FILE *fout=fopen(fname,"w");		//opening file to print .dot file of the adjacency matrix			
	if(printDot(fout,adjMat,size,colour)==INT_MIN)
	{
		printf("Error opening file.\nExiting.........\n");
		return 0;
	}
	printf("File successfully printed.\n");
	fclose(fout);			//disconnecting the file from stream
	return 0;
}


