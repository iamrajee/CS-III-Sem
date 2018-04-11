#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct student{
	char name[20];
	int id;
};
int main(){
	struct student *list;
	int N,i;
	printf("Enter the N:");
	scanf("%d",&N);
	list = (struct student*) malloc(N*sizeof(struct student*));
	//ptr = (struct student*) calloc(N, sizeof(struct student));
	//struct student stu[N];
	printf("\nEnter the name and id of students\n");
	for(i=0; i<N; i++){
		printf("%d.)",(i+1));
		scanf("%s", stu[i].name);
		scanf("%d", &stu[i].id);
	}
	int max=0,maxid;
	for(i=0; i<N; i++){
		if(stu[i].id>max){
			max = stu[i].id;	
			maxid = i;
		}
	}
	printf("\nstudent with the maximum id is:%s\n", stu[maxid].name);
	return 0;
}
