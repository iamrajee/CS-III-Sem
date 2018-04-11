//checks whether a given vertex can be inserted at a given postion in the HAM path
int check(int a[][100],int vertex,int size,int ham[],int pos);

//to make the hamiltionian cycle in the given array and return 0 if not possible
int make_ham_cycle(int a[][100],int size,int ham[],int pos);

//function to print ham cycle edges in red
void print_ham_path(int ham[],int size,int a[][100],FILE *foo);
