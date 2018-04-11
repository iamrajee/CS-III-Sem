#define MAX 100

#define initial 1
#define waiting 2
#define visited 3

int state[MAX]; 
int parent[MAX];
int distance[MAX];
int level[MAX];

int BFS(int v,int v1);
void BF_Traversal(int v, int v1);
