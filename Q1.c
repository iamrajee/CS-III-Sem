/*Rajendra singh, 1 aug 2017*/
#include<stdio.h>
#include<string.h>
struct student{   			//defining structure
	char name[20];
	int id;
};
void PrintStruc( struct student*);	//declaration of function
int main(){
	struct student stud1;
	strcpy(stud1.name, "rajendra");		//initialising the structure variable
	stud1.id = 111601017;
	struct student *srtptr;
	srtptr = &stud1;		//define point to structure
	PrintStruc(srtptr);//calling the function
	strcpy(srtptr->name, "abc");	//using pointer to change struct variable 
	(*srtptr).id = 123;
	PrintStruc(srtptr);
	return 0;
}

void PrintStruc(struct student*p){	//defining the function
	printf("%s\n", (*p).name);
	printf("%d\n", (*p).id);
} 
