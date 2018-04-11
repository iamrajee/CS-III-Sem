// C program to evaluate value of a postfix expression
//rajendra singh
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 
// Stack declaration
struct Stack
{
    int top;
    int size;
    int* array;
};
 
// Stack creation
struct Stack* createStack( int size)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));//memery allocation
 
    stack->top = -1;//top value is allocated
    stack->size=size;
    stack->array = (int*) malloc(stack->size* sizeof(int));//array of given size is allocated memory
    return stack;
}
 //function to check for empty
int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ;
}
 
char peek(struct Stack* stack)//returns top element and top is decremented
{
    return stack->array[stack->top];
}
 
char pop(struct Stack* stack) //popinig function
{
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return 'e';//returns when stack is empty
}
 
void push(struct Stack* stack, char op)//function to push element to stack
{
    stack->array[++stack->top] = op;
}
 
 
// The  function that returns value of a given postfix expression
int evaluatePostfix(char* exp)
{
    // Create a stack of capacity equal to expression size
    struct Stack* stack = createStack(strlen(exp));
    int i;
 
    // See if stack was created successfully
    if (!stack) return -1;
 
    // Scan all characters one by one
    for (i = 0; exp[i]; ++i)
    {
        // If the scanned character is an operand  push it to the stack.
        
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');
 
        //  If the scanned character is an operator, pop two  elements from stack apply the operator
        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i])
            {
             case '+': push(stack, val2 + val1); break;
             case '-': push(stack, val2 - val1); break;
             case '*': push(stack, val2 * val1); break;
             case '/': push(stack, val2/val1);   break;
            }
        }
    }
    return pop(stack);
}
 
// program to test above functions
int main()
{
    char exp[] = "2*3+4-5";
    printf ("Value of %s is %d\n", exp, evaluatePostfix(exp));
    return 0;
}
