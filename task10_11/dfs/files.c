#include<stdio.h>
#include "files.h"

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
		fscanf(adj,"%c", &junk); //reads from the input file
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

/* function to create dot file of the graph */
void gen_dot()
{
	FILE *dot; //dot is afile pointer
	int i,j; //i and j are integer variables

	dot=fopen(outfile, "w"); //opens the file to write
	fprintf(dot,"graph %s{\n", name); //writes to the output file

	/* nested loop to write to output file */
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			if(b[i][j]!='0')
			{
				b[j][i]='0';				
				fprintf(dot,"%d -- %d",i,j); //writes to the output file
				if(b[i][j]=='1')
					fprintf(dot, ";\n");
				else if(b[i][j]=='2')
					fprintf(dot, " [color=red] ;\n");
			}
		}
	}

	fprintf(dot,"}"); //writes to the output file
	fclose(dot); //closes output file
}
