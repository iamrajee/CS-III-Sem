/* Global Variables */
char name[10];
char infile[40];
char outfile[40];
char a[30][30];
char b[30][30];
int size;
int visited[30];

int read_adj();
void copy_adj();
void gen_dot();
