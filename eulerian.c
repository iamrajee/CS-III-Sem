/* Programmer's Name: Sachin Hansda
   Prorgram Name: eulerian.c
   Program Description: Write a C program to find an Eulerian circuit in a given graph, if it has one.
                        User inputs: Name of the file containing adjacency matrix of the graph (string) and starting node (int)
                        Output: If the graph is Eulerian, print the sequence of vertices in the Eulerian circuit starting from the designated vertex.  Otherwise, print "No."
   Date: 10/10/17 */

#include<stdio.h>

/* Global Variables */
char infile[40];
char a[30][30];
int visited[30];
int degree[30];
int evod[30];
int visited[30];
int size,start;

/* function to read the adjaceny matrix of the graph */
int read_adj()
{
	FILE *adj; //adj is file pointer
	char name[10], type[10],junk; //name & type are single dimension character array, junk is a character variable, a is double dimension character array
	int i,j; //size, i and j are integer variables
	adj=fopen(infile, "r"); //opens the file to read
	
	/* checks whether the input file contains any data or not */
	if (adj == 0)  
	{
		printf("Error in opening the file\n"); //displays error message
		return(1); //returns 1 if input file does not contain any data
	}

	fscanf(adj,"%s %s", name, type); //reads from the input file
	fscanf(adj,"%d", &size); //reads from the input file
	fscanf(adj,"%c", &junk); //reads from the input file

	/* nested loop to scan the data from input file */
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			fscanf(adj, "%c", &a[i][j]); //reads from the input file
		}
		fscanf(adj,"%c", &junk); //raeds from the input file
	}
	fclose(adj); //closes input file
	return 0;
}

/* function to find degree of a vertex */
int find_deg(int k)
{
	int i, j,d=0; //i,j and d are integer variables

	/* loop to find degree */
	for(i=0; i<size; i++)
	{
		if(a[k][i]=='1')
			d++;
	}
	return d;
}

/* function to create a list which contains degree of all the vertices */
void deg_list()
{
	int i; //i is integer variables
	for(i=0; i<size; i++)
		degree[i]=find_deg(i); //calls the function find_deg to find degree of a vertex
}

/* Function to create a list which tells whether a vertex has even degree or odd degree */
void check_deg()
{
	int i; //i is integer variable
	deg_list();// calls the function deg_list

	/* loop to check whether vertices has even degree or odd degree */
	for(i=0; i<size; i++)
	{
		if(degree[i]%2==0)
			evod[i]=0;
		else
			evod[i]=1;
	}
}

/* Function to check whether every vertex of the graph has even degree or odd degree.
   If k is 0, it will check for even degree.  If k is 1, it will check for odd degree.
   If all the vertices are even, then it will return 1. It will work similarly for odd. It will return 0 if some vertices are odd and some are even */
int check_deg_list(int k)
{
	int i,ck=1; //i and ck are integer variables
	check_deg(); //calls the function check_deg

	for(i=0; i<size; i++)
	{
		if(evod[i]!=k)
		{
			ck=0;
			break;
		}
	}
	return ck;
} 

/* function to print the sequence eulerian circuit follows */
void euler_cir()
{
	int even,route,ck,ck1,i,j; //even, route, ck, ck1, i and j are integer variables
	even=check_deg_list(0); //calls the function check_deg_list

	if(even==0)
		printf("Graph is not Eulerian\n"); //displays a message

	else
	{
		printf("Eulerian Circuit:\n"); //displays a message
		route=start;
		visited[start]=1;
		printf("%d  ", route); //prints the first vertex in the sequence

		/* nested loop to print the circuit */
		do
		{
			ck=0;
			for(i=0; i<size; i++)
			{
				ck1=0;
				if(a[route][i]=='1')
				{
					if(visited[i]==1)
					{
						/* loop to check if there any other unvisited path which goes through an unvisited vertex */
						for(j=(i+1); j<size; j++)
						{
							if(a[route][j]=='1' && visited[j]!=1)
							{
								ck1=1;
								a[route][j]='0';
								a[j][route]='0';

								visited[j]=1; //updates the visited array
								route=j; //updates the route
								printf("%d  ", route); //prints the next vertex in the sequence

								break;
							}
						}
					}
					if(ck1==0)
					{
						a[route][i]='0';
						a[i][route]='0';

						visited[i]=1; //updates the visited array
						route=i; //updates the route
						printf("%d  ", route); //prints the next vertex in the sequence
					}
				}
			}
			for(i=0; i<size; i++)
			{
				if(a[route][i]=='0')
					ck++;
			}
		}
		while(ck<size);

		printf("\n");

	}
}

int main()
{
	int rt; //rt is integer variable

	printf("Enter the input filename\n"); //Prompts the user to enter the input filename
	scanf("%s", infile); //scans the input filename

	printf("Enter the starting node\n"); //Prompts the user to enter the starting node of the desired eulerian circuit
	scanf("%d", &start); //scans the starting node of the desired eulerian circuit

	rt=read_adj(); //calls the function read_adj
	euler_cir(); //calls the function euler_cir

	return 0; //tells the compiler that everything went well
}
	
	
