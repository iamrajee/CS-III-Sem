/* Programmer's Name: Sachin Hansda
   Prorgram Name: dfs_tree.c
   Program Description: Write a C program which given an input graph G (as adjacency matrix) and a starting node r, computes a DFS tree of G rooted at r. Highlight the edges of the DFS tree in a different colour in the dot file.
   Date: 31/10/17 */

#include<stdio.h>
#include<stdlib.h>
#include "files.h"
#include "stack.h"
#include "stack_dfs.h"

int main()
{
	int v;
	printf("Enter the input file\n");
	scanf("%s", infile);
	read_adj();
	copy_adj();
	printf("enter the root\n");
	scanf("%d", &v);
	DFS(v);
	printf("Enter the output file\n");
	scanf("%s", outfile);
	gen_dot();
	return 0;
}
