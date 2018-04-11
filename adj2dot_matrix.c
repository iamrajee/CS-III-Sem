//RAJENDRA SINGH
//111601017
//PROGARM FOR READING THE ADJECENCY MATRIX OF GRAPH
//03-10-17 


#include<stdio.h>
void adj2dot(char* , char*);
int main(){
	char filename[20];
	char dotfilename[20];
	printf("Enter the graph adjency file name\n");		//Asking for the file name
	scanf("%s", filename);
	printf("Enter the graph dot file name that you would like to keep\n");		//Asking for the file name
	scanf("%s", dotfilename);
	adj2dot(filename, dotfilename);
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
