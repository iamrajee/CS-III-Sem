#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "files.h"

void DFS(int v)
{
	int c,v1,i,c1=1;
	stack S,S1=NULL;
	for(i=0; i<size; i++)
		visited[i]=0;
	c=IsEmpty(S);
	if(c==(-1))
		S=create();
	S=(stack)malloc(sizeof(struct stack));
	Push(S,v);
	visited[v]=1;
	S->next=S1;
	S1=S;
	while(S!=NULL && c1==1)
	{
		c1=0;
		for(i=0; i<size;i++)
		{
			if(visited[i]==0)
			{
				c1=1;
				break;
			}
		}
		v1=Pop(S);
		S=S->next;
		S1=S;
		for(i=0; i<size; i++)
		{
			if(a[v1][i]=='1')
			{
				if(visited[i]!=1)
				{
					b[v1][i]='2';
					b[i][v1]='2';
					c=IsEmpty(S);
					if(c==(-1))
						S=create();
					S=(stack)malloc(sizeof(struct stack));
					Push(S,i);
					visited[i]=1;
					S->next=S1;
					S1=S;
				}
			}
		}
	}
}
