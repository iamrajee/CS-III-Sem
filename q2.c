#//RAJENDRA SINGH
//111601017
//PROGARM FOR FINDING IF TWO NODES ARE CONNECTED OR NOT
//03-10-17 


#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* link;
};
 
struct Queue
{
    struct Node *front, *rear;
	int capacity;
};
 
void adj2dot(char* , char*);
void BFS(char*, int, int); 
struct Queue* createQueue(int capacity);
void enQueue(struct Queue*, int);
int deQueue(struct Queue*);
int main(){
	int root, goal;
	char filename[20];
	char dotfilename[20];
	printf("Enter the graph adjency file name\n");		//Asking for the file name
	scanf("%s", filename);
	printf("Enter the graph dot file name that you would like to keep\n");		//Asking for the file name
	scanf("%s", dotfilename);
	adj2dot(filename, dotfilename);
	BFS(filename, root, goal);
return 0;
}



void adj2dot(char* filename, char* dotfilename){
	
	FILE * fptr;	//file pointer
	int i = 0;
	int r,w,success, size, j;
	char line[200];		
	char b;
	int a[50][50];		//variable for reading matrix entries as character
	int check = 0;
	
	fptr = fopen(filename, "r");			//Creating a file and assigning its address to file pointer
	if(fptr == NULL){				//checking if file creted or not
		printf("Error in opening the file\n" );
		return;
	}
	else{

		for(i=0;i<2;i++){				//scaning the first 2 lines from file
			success = fscanf(fptr, "%s", line);
			if(success == -1) break; 
			printf("%s\n", line);
			
		}
		


 		success = fscanf(fptr, "%d", &size);		//reading the size i.e 3rd line
		printf("%d", size);

		

		for(i=0; i<size; i++){				//scaning the matrix element on eby one as char
			printf("\n");
			for(j=0; j<size; j++){
				success = fscanf(fptr, "%1d", &a[i][j]);
				printf("%d ", a[i][j]);
			}
			
		}
		printf("\n");
	}
	fclose(fptr);						//closing the file




	fptr = fopen(dotfilename, "w");			//creating new dot file as writable 
	if(fptr == NULL){
		printf("Error in opening the file\n" );			//checking if file creted or not
		return;
	}
	fprintf(fptr, "graph %s{\n", &line[0]);				//writing the first line in dot file

	for(i=0; i<size; i++){						//checking and writing the adjecency matrix element relation 
		for(j=i; j<size; j++){
			if(a[i][j] == 1){
				fprintf(fptr,"%d--%d;\n", i, j);
				check = 1;
			}
		}

		if(check == 0){
			fprintf(fptr, "%d;\n", i);
		}
	}
	fprintf(fptr,"}");					//writing the last line
	fclose(fptr);			//closing the dot file
	
}

void BFS(char *filename, int root, int goal){
	
	FILE * fptr;	//file pointer
	int i = 0;
	int r,w,success, size, j;
	char line[200];		
	char b;
	int a[50][50];		//variable for reading matrix entries as character
	
	fptr = fopen(filename, "r");			//Creating a file and assigning its address to file pointer
	if(fptr == NULL){				//checking if file creted or not
		printf("Error in opening the file\n" );
		return;
	}
	else{

		for(i=0;i<2;i++){				//scaning the first 2 lines from file
			success = fscanf(fptr, "%s", line);
			if(success == -1) break; 
			printf("%s\n", line);
			
		}
		


 		success = fscanf(fptr, "%d", &size);		//reading the size i.e 3rd line
		printf("%d", size);

		

		for(i=0; i<size; i++){				//scaning the matrix element on eby one as char
			printf("\n");
			for(j=0; j<size; j++){
				success = fscanf(fptr, "%1d", &a[i][j]);
				printf("%d ", a[i][j]);
			}
			
		}
		printf("\n");
	}
	fclose(fptr);						//closing the file

	
	int visited[size];
	int current;
	
	for(i=0; i<size; i++){
		visited[i] = 0;
 	}
	
	visited[root] = 1;

	struct Queue* q = createQueue(size);
	//struct Queue q;
	enQueue(q, root);
	while(q->front != NULL){
		current  = deQueue(q);
		if(current == goal){
			printf("Yes connected\n");
			return;
		}	
		else{
			for(j=0;j<size; j++){
				if(a[current][j] == 1){
					if(visited[j] == 0){
						visited[j] = 0;
						enQueue(q,j);
					}
				}
			}
		}
	}
	
}

// function to create a queue of given capacity. 
// It initializes size of queue as 0
struct Queue* createQueue(int capacity)
{
    struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->front = 0; 
    q->rear = 0;
    return q;
}

// Function to create Circular queue
void enQueue(struct Queue *q, int value)
{
    struct Node* temp;
    temp->data = value;
    if (q->front == NULL)
        q->front = temp;
    else
        q->rear->link = temp;
 
    q->rear = temp;
    q->rear->link = q->front;
}


// Function to delete element from Circular Queue
int deQueue(struct Queue *q)
{
    if (q->front == NULL)
    {
        printf ("Queue is empty");
        //return INT_MIN;
    }
 
    // If this is the last node to be deleted
    int value; // Value to be dequeued
    if (q->front == q->rear)
    {
        value = q->front->data;
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
    }
    else  // There are more than one nodes
    {
        struct Node *temp = q->front;
        value = temp->data;
        q->front = q->front->link;
        q->rear->link= q->front;
        free(temp);
    }
 
    return value ;
}
 
