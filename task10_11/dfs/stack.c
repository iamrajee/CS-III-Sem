#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

/* function to a create a new stack */
stack create()
{
	static stack stk;
	stk=(stack)malloc(sizeof(struct stack));
	return stk;
}

/* function to push a new node */
void Push(stack stk, int x)
{
	stk->vertex=x;
}

int Pop(stack stk)
{
	stack stk1;
	static int a;
	stk1=stk;
	a=stk1->vertex;
	stk=stk->next;
	//free(stk1);
	return a;
}

/* function to check whether stack is empty */
int IsEmpty(stack stk)
{
	if(stk==NULL)
		return -1;
	else
		return 1;
}

