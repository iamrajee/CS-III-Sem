#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "files.h"
#include "stack_dfs.h"

int main()
{
	int i;
	printf("Enter input filename\n");
	scanf("%s", infile);
	read_adj();
	DFS();
	if(count==0)
		printf("There are no cut vertices in the graph\n");
	else
	{
		printf("Cut vertices are:\n");
		for(i=0; i<count; i++)
			printf("%d,  ", cut[i]);
		printf("\n");
	}
	return 0;
}
