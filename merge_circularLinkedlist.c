//Rajendra singh, 4 Aug 2017
//For merging two cicular linked list
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{				//defining structure node
	int data;
	struct node* link;
};
struct node *roottemp=NULL, *root1=NULL, *root2=NULL, *root3=NULL;
int i, N1, N2, val;
void Append(void);											//declaring various function
void DeleteofValue(void);
void SearchofValue(void);
int LengthofList(void);
void Mergelists(void);
int ch;
int main(){
	while(1){
		printf("1.Append List1(i.e add node at end of cicular list1)\n");				//giving various operation choice to user 
		printf("2.Append List2(i.e add node at end of cicular list2)\n");
		printf("3.DeleteofValue in List1(i.e delete the node of given value)\n");
		printf("4.DeleteofValue in List2(i.e delete the node of given value)\n");
		printf("5.Merge the both circular lists, i.e 1&2");
		printf("6.Quit\n\n");
		printf("Enter your choice : ");
		scanf("%d", &ch);													//reading the user choice
	
		switch(ch){										//switch operation for user given chioce
			case 1: roottemp = root1;
					Append();
					root1 = roottemp;
					break;
			case 2: roottemp = root2;
					Append();
					root2 = roottemp;
					break;
			case 3: roottemp = root1;
					DeleteofValue();
					root1 = roottemp;
					break;
			case 4: roottemp = root2;
					DeleteofValue();
					root2 = roottemp;
					break;
			case 5: Mergelists();
					break;
			case 6:  exit(1);
			
			default : printf("\n\nInvalid choice! Please re-enter your choice...\n\n");
		}
	}
	return 0;
}

void Append(){										//function for adding node at end of cicular list1
	struct node *temp,*p;
	temp = (struct node*) malloc(sizeof(struct node));
	printf("Enter the data value\n");
	scanf("%d", &temp->data);
	temp->link = NULL;
	if(roottemp == 0){
		roottemp = temp;
	
	}
	else{
		p = roottemp;
		for(i=0;p->link != roottemp;i++){
			p = p->link;
		}
		p->link = temp;
		temp->link = roottemp;
	}
	free(temp);
	free(p);
	
}

void DeleteofValue(){								//function for deleting the node of given value
	struct node *temp,*p;
	printf("Enter the value of node data to be deleted\n");
	scanf("%d", &val);
	
	p = roottemp;
	if(p->link == roottemp){
		if(p->data == val){
			roottemp = NULL;
		}
	}
	else{
		for(i=0;p->link != roottemp;i++){
			if((p->link)->data == val){
				temp = p->link;
				p->link = temp->link;
				temp->link = NULL;
			
			}
			p = p->link;
		}
	}
	free(temp);
	free(p);
}
	
void Mergelists(void){									//function for  Mergeing the both circular lists, i.e 1&2					
	struct node *p2, *temp1, *temp2, *p1;
	roottemp = root1;
	N1 = LengthofList();
	roottemp = root2;
	N2 = LengthofList();
	
	p2 = root2;
	p1=root1;
	if(N1>N2){
		while(p2->link != root2){
			temp2 = p2->link;
			temp1 = p1->link;
				
			
			p2->link = p1->link;
			p1->link = p2;
				
			p1 = temp1;
			p2 = temp2;
		}
	}
	else{
		printf("Size of list 1 is =< size of list 2 !!! So please first add sum more elemant in list 1.\n");
	}
}

int LengthofList(){							//function for finding length of circular linked list				
	struct node *p;
	if(roottemp == NULL){
		return 0;
	}
	if(p->link == NULL){
		return 1;
	}
	else{
		for(i=0;p->link != 0;i++){
			p = p->link;
		}
		return i;
	}
	free(p);
}

