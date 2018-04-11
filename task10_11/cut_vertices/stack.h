struct stack
{
	int vertex;
	struct stack *next;
};

typedef struct stack *stack; //defining a new type of variable

stack create();
void Push(stack, int);
int Pop(stack);
int IsEmpty(stack);
