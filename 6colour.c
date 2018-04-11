/* Programmer's Name: Sachin Hansda
   Prorgram Name: 6colour.c
   Program Description: Write a C program which properly colours the vertices of an input planar graph using 6 colours.
                        First create a 5-degenerate sequence of vertices and then colour them in the reverse order. You can maintain the 5-degenerate sequence as an array. 
			User inputs: Name of the file containing adjacency matrix of the graph (string)
			Output: A dot file for the graph with the vertex coloured using at most six colours
   Date: 16/10/17 */

#include<stdio.h>

/* Global Variables */
char name[10];
char infile[40];
char a[30][30];
char b[30][30];
int fivedegen[30];
int visited[30];
int degree[30];
int size;

/* function to read the adjaceny matrix of the graph */
int read_adj()
{
	FILE *adj; //adj is file pointer
	char type[10],junk; //type are single dimension character array, junk is a character variable, a is double dimension character array
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

/* function to make a copy of adjaceny matrix of the graph */
void copy_adj()
{
	int i,j; //size, i and j are integer variables

	/* nested loop to copy DDA a to DDA b */
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			b[i][j]=a[i][j]; 
		}
	}
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

/* function to create the 5 degenerate sequence */
void five_degenerate()
{
	int i,j,rt,c=0,ck,t; //i,j,rt,c,ck and t are integer variables

	/* nested to create the 5 degenerate sequence in reverse order */
	do
	{
		for(i=0; i<size; i++)
		{
			ck=0;

			/* loop to check if a vertex is already in reverse 5 degenerate sequence */
			for(j=0; j<c; j++)
			{
				if(i==fivedegen[j])
				{
					ck=1;
					break;
				}
			}

			/* block to add a new vertex in the reverse 5 degenerate sequence */
			if(ck==0)
			{
				rt=find_deg(i);
				if(rt<=5)
				{
					fivedegen[c]=i;
					c++;
					for(j=0; j<size; j++)
					{
						a[c][i]='0';
						a[i][c]='0';
					}
				}
			}
		}
	}
	while(c<size);

	/* loop to reverse the fivedegen array making 5 degenerate sequence in correct order */
	for(i=0; i<size; i++)
	{
		t=fivedegen[size-1];
		for(j=(size-1); j>0; j--)
			fivedegen[j]=fivedegen[j-1];
		fivedegen[0]=t;
	}
}

/* function to create dot file of the graph */
void gen_dot()
{
	FILE *dot; //dot is afile pointer
	int i,j; //i and j are integer variables

	dot=fopen("outfile.dot", "w"); //opens the file to write
	fprintf(dot,"graph %s{\n", name); //writes to the output file

	/* nested loop to write to output file */
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			if(b[i][j]=='1')
			{
				b[j][i]='0';
				fprintf(dot,"%d -- %d ;\n",i,j); //writes to the output file
			}
		}
	}

	/* to add colour to the vertices */
	for(i=(size-1); i>=0; i=i-6)
		fprintf(dot, "%d [color=red, style=filled];\n", fivedegen[i]);
	for(i=(size-2); i>=0; i=i-6)
		fprintf(dot, "%d [color=azure, style=filled];\n", fivedegen[i]);
	for(i=(size-3); i>=0; i=i-6)
		fprintf(dot, "%d [color=cyan, style=filled];\n", fivedegen[i]);
	for(i=(size-4); i>=0; i=i-6)
		fprintf(dot, "%d [color=gold, style=filled];\n", fivedegen[i]);
	for(i=(size-5); i>=0; i=i-6)
		fprintf(dot, "%d [color=bisque, style=filled];\n", fivedegen[i]);
	for(i=(size-6); i>=0; i=i-6)
		fprintf(dot, "%d [color=blue, style=filled];\n", fivedegen[i]);

	fprintf(dot,"}"); //writes to the output file
	fclose(dot); //closes output file
}
	
int main()
{
	int rt; //rt is integer variable

	printf("Enter the input filename\n"); //Prompts the user to enter the input filename
	scanf("%s", infile);  //scans the input filename

	rt=read_adj(); //calls the function read_adj
	copy_adj(); //calls the function copy_adj
	five_degenerate(); //calls the function five_degenerate
	gen_dot(); //calls the function gen_dot

	return 0; //tells the compiler that everything went well
}
	

