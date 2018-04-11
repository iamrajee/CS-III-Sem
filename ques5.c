//Rajendra singh, 4 Aug 2017
//q2 repeated with doubly linked list
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Student {
	int id;
	char name[20];
	struct Student *next;
	struct Student*prev;
};
int N, i, max, maxid;
struct Student *list = 0;
int main(){
	printf("Enter the Number of student : ");
	scanf("%d", &N);
	printf("Enter the students name and id\n");
	for(i=0; i<N; i++){
		list = (struct Student*) malloc(N*sizeof(struct Student));
		
		if(i==0){
			(list + i)->next = list + (i+1);
			(list + i)->prev = 0;
		}
		if(i>0 && i<(N-1)){
			(list + i)->next = list + (i+1);
			(list + i)->prev = list + (i-1);
		}	
		if(i==(N-1)){
			(list + i)->next = 0;
			(list + i)->prev = list + (i-1);
		}
		printf("%d. ", i+1);
		scanf("%s[^\n]",(list + i)->name );
		scanf("%d",&(list + i)->id );
		
	}
	max = list->id;
	for(i=0; i<N; i++){
		
		if((list+i)->id >= max){
			max = (list+i)->id;
			maxid = i;
		}
		
	}
	
	printf("%s has the maximum id", (list + maxid)->name);
	
}



	
	
	
