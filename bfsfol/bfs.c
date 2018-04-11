#include<stdio.h>
#include "bfs.h"
#include "files.h"
#include "Qarray.h"

int BFS(int v,int v1)
{
	int i, blue=0;
	if(v==v1)
		return 1;
	
	insert_queue(v);
	state[v] = waiting;
	
	while(!isEmpty_queue())
	{
		v = delete_queue( );
		if(v==v1)
			return 1;
		state[v] = visited;
		level[v]=0;
		
		for(i=0; i<size; i++)
		{
			if(b[v][i] != '0' && state[i] == initial) 
			{
				level[i]=level[v]+1;
				parent[i]=v;
				insert_queue(i);
				state[i] = waiting;
			}
		}
	}
	return 0;
}

void BF_Traversal(int v, int v1)
{
	int v2, dist=0,rt,j;
	for(j=0; j<size; j++) 
		state[j]=initial;
		v2=v1;
				rt=BFS(v,v1);
				if(rt==1)
				{
					do
					{
						if(v2==v)
							break;
						v2=parent[v2];
						dist++;
					}
					while(v2!=v);
				}
	printf("Distance=%d\n", dist);
}

