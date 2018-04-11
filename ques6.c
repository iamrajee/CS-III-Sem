//Rajendra singh, 4 Aug 2017
//For merging two cicular linked list
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{				//defining structure node
	int data;
	struct node* link;
};
struct node *roottemp=0, *root1=0, *root2=0, *root3=0;
int i=0, N1, N2;
void Append(void);											//declaring various function
void Mergelists(void);
void display(struct node *);
int main(){
	
	printf("Enter the size N1 of first circular linked list\nN1 : ");				//creating the first circular linked list 
	scanf("%d", &N1);
	printf("Enter the %d node data's of first circular linked list\n", N1);
	
	roottemp = root1;
	i = 0;
	while(i < (N1-1)){
		Append();	
		i++;
	}
	root1 = roottemp;
	display(root1);
	printf("\n");
	
	
	
	printf("Enter the size N2( < N1) of second circular linked list\nN2 : ");					//creating the second circular linked list 
	scanf("%d", &N2);
	while(N2 > N1){
		printf("N2 > N1, Please enter the correct size of second cicular linked list\n N2 : ");
		scanf("%d", &N2);
	}
	printf("Enter the %d node data's of second circular linked list\n", N2);
	
	roottemp = root2;
	i = 0;
	while(i < (N2-1)){
		Append();	
		i++;
	}
	root2 = roottemp;
	display(root2);
	printf("\n");
	
	
	
	Mergelists();
	
	display(root1);
	printf("\n");
	
	
	free(roottemp);
	return 0;
}

void Append(){									//function for adding node at end of cicular list
	struct node *temp = NULL,*p = NULL;
	temp = (struct node*) malloc(sizeof(struct node));
	scanf("%d", &temp->data);
	temp->link = NULL;
	if(roottemp == 0){
		roottemp = temp;
		temp->link = roottemp;
	
	}
	else{
		p = roottemp;
		for(i=0;p->link != roottemp;i++){
			p = p->link;
		}
		p->link = temp;
		temp->link = roottemp;
	}

}
	
void Mergelists(void){									//function for  Mergeing the both circular lists, i.e 1&2					
	struct node *p2 = NULL, *temp1 = NULL, *temp2 = NULL, *p1 = NULL;
	p2 = root2;
	p1=root1;
	while(p2->link != root2){
		temp2 = p2->link;
		temp1 = p1->link;
				
			
		p2->link = temp1;
		p1->link = p2;
				
		p1 = temp1;
		p2 = temp2;
	}
	if(p2->link == root2){
		temp1 = p1->link;
				
			
		p2->link = temp1;
		p1->link = p2;
	}
		
}

void display(struct node *roottemp){					//function for displaying any circular linked list
	struct node *p;
	p = roottemp;
	if(p->link == roottemp){
		printf("%d-->", p->data);
	}
	else{
		while(p->link != roottemp){
			printf("%d-->", p->data);
			p = p->link;
		}
		if(p->link == roottemp){
			printf("%d-->", p->data);
		}
	}

}
