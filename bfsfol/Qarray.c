#include<stdio.h>
#include "Qarray.h"

/* function to insert a node in the queue */
void insert_queue(int vertex)
{
	if(rear == MAX-1)
		printf("Queue Overflow\n");
	else
	{
		if(front == -1) 
			front = 0;
		rear = rear+1;
		queue[rear] = vertex ;
	}
}

/* function to check if the queue is empty */
int isEmpty_queue()
{
	if(front == -1 || front > rear)
		return 1;
	else
		return 0;
}

/* function to delete a node from the queue */
int delete_queue()
{
	int delete_item;
	if(front == -1 || front > rear)
	{
		printf("Queue Underflow\n");
		return -1;
	}
	delete_item = queue[front];
	front = front+1;
	return delete_item;
}

