#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "files.h"
#include "stack_dfs.h"

void DFS()
{
	int c,v1,i,c1=1,j,k,v;
	count=0;
	stack S,S1=NULL;
	for(i=0; i<size; i++)
	{
		copy_adj();
		for(j=0; j<size; j++)
			visited[j]=0;
		visited[i]=1;
		for(j=0; j<size; j++)
		{
			if(b[i][j]=='1')
			{
				v=j;
				b[i][j]='0';
				b[j][i]='0';
			}
		}
		c=IsEmpty(S);
		if(c==(-1))
			S=create();
		S=(stack)malloc(sizeof(struct stack));
		Push(S,v);
		visited[v]=1;
		S->next=S1;
		S1=S;
		while(S!=NULL)
		{
			c1=0;
			for(k=0; k<size;k++)
			{
				if(visited[k]==0)
				{
					c1=1;
					break;
				}
			}
			v1=Pop(S);
			S=S->next;
			S1=S;
			for(k=0; k<size; k++)
			{
				if(a[v1][k]=='1')
				{
					if(visited[k]!=1)
					{
						c=IsEmpty(S);
						if(c==(-1))
							S=create();
						S=(stack)malloc(sizeof(struct stack));
						Push(S,k);
						visited[k]=1;
						S->next=S1;
						S1=S;
					}
				}
			}
		}
		if(c1==1)
		{
			cut[count]=i;
			count++;
		}
	}
}
