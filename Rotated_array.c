//Rajendra singh 
//rotated array

#include<stdio.h>
#include<stdlib.h>


int FindRotate(int *, int );
int main()
{
	int *List;
	int n,i,mini,c=0,target; 
	
	printf("Enter the length of array\n"); 
	scanf("%d", &n); 				//reading the length
	List=(int*)malloc(n*sizeof(int)); 			//creating list dynamically
	printf("Enter the elements of the array\n");		
	
	for(i=0; i<n; i++)					//reading the elements
		scanf("%d", &List[i]); 
		
	mini=0;
	
	for(i=1; i<n; i++)
	{
		if(List[mini]>List[i])			//finding minimum index
			mini=i;
	}

	for(i=mini; i<(n-1); i++)
	{
		if(List[i]>List[i+1])
		{
			c=1;
			break;
		}
	}
	if(c==0 && mini!=0)
	{
		if(List[n-1]>List[0])
			c=1;
	}
	if(c==0 && mini!=0)
	{
		for(i=0; i<(mini-1); i++)
		{
			if(List[i]>List[i+1])
			{
				c=1;
				break;
			}
		}
	}
	
	if(c==1)
		printf("Error: The array is not in rotated ascending order\n"); 
	
	else if(c==0)
	{
		printf("Enter the target\n"); 
		scanf("%d", &target);				//reading target
		
		i=FindRotate(List,target);				//finding target
		if(i==(-1))
			printf("Target is not present in the array\n");
		else
			printf("Index of target element in the list is %d\n", i);
	}
	
	free(List);
	
	return 0;
}


int FindRotate(int *List, int target) //finding targrt
{
	int i=0; 
	
	while(List[i]!='\0')			//checking target
	{
		if(List[i]==target)
			return i;
		i++;
	}
	
	return -1;
}
	
		
		

