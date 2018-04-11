/*Programmer's Name: Sachin Hansda 
  Program Name: search_matrix.c
  Program Description: Given a matrix of integers in which each row and each column is sorted, write a function to find an element in it
  Date: 18/9/17 */

/* Assumptions: 1. Since no specific search algorithm was asked in question, I have used linear search algorithm 
		2. For printing, index of first row is 1 and not 0, similarly for column 
		3. Matrix created is not of the exact order as the user wanted
		4. It not work if the row>100 or column>100 */

#include<stdio.h>
#include<stdlib.h>

/* function to find the required element */
void search(int a[100][100], int n, int m, int src)
{
	int i,j,c=0; // i, j and c are integer variables

	/* nested loop to find the required element */
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		{
			if(a[i][j]==src)
			{
				c=1;
				printf("Required element is present in row-%d and column-%d\n", i+1,j+1); //displays a message
				break;
			}
		}
		if(c==1)
			break;
	}

	if(c==0)
		printf("Required element is not present in the matrix\n"); //displays a message

}

int main()
{
	int a[100][100], n, m, src, i, j,c; //a is double dimensional integer array and n,m,src,i,j and c are integer variables

	printf("Enter the row length of the matrix\n"); //prompts the user to enter the row length of the array
	scanf("%d", &n); //scans the row length of the array
	printf("Enter the column length of the matrix\n"); //prompts the user to enter the column length of the array
	scanf("%d", &m); //scans the column length of the array

	printf("Enter the elements of the matrix\n"); //prompts the user to enter the elements of the matrix

	/* loop to scan the elements of the matrix */
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
			scanf("%d", &a[i][j]);
	}

	if(a[i][j]>a[i][j])
		c=2;
	else
		c=1;

	/* to check if the rows and columns of the matrix are in descending order */
	if(c==2)
	{
		/* to check if the rows of the matrix are in descending order */
		for(i=0; i<n; i++)
		{
			for(j=0; j<(m-1); j++)
			{
				if(a[i][j]<a[i][j+1])
				{
					c=0;
					break;
				}
			}
			if(c==0)
				break;
		}

		/* to check if the columns of the matrix are in descending order */
		if(c==2)
		{
			for(i=0; i<m; i++)
			{
				for(j=0; j<(n-1); j++)
				{
					if(a[j][i]<a[j+1][i])
					{
						c=0;
						break;
					}
				}
				if(c==0)
				break;
			}
		}
	}

	/* to check if the rows and  columns of the matrix are in ascending order */
	if(c==1)
	{
		/* to check if the rows of the matrix are in ascending order */
		for(i=0; i<n; i++)
		{
			for(j=0; j<(m-1); j++)
			{
				if(a[i][j]>a[i][j+1])
				{
					c=0;
					break;
				}
			}
			if(c==0)
				break;
		}

		/* to check if the columns of the matrix are in ascending order */
		if(c==1)
		{
			for(i=0; i<m; i++)
			{
				for(j=0; j<(n-1); j++)
				{
					if(a[j][i]>a[j+1][i])
					{
						c=0;
						break;
					}
				}
				if(c==0)
				break;
			}
		}
	}

	if(c==0)
		printf("Error: The matrix is not fully sorted\n"); //displays a message

	else
	{
		printf("Enter the element to be searched\n"); //prompts the user to enter a element to be searched
		scanf("%d", &src); //scans the element
		search(a,n,m,src); //calls the function search
	}

	return 0; //tells the compiler that everything went well
}
	
