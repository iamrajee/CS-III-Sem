//program to convert infix to postfix expression
//name rajendra singh
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
 //functions used
void expression_conversion();
int check_space_tabs(char character);
void push(long int character);
int pop();
int priority(char character);
int isEmpty();
 //global variables
int top;
long int stack[50];
char infix_expression[50], postfix_expression[50];
 
int main()
{
      top = -1;
      printf("\nEnter an Expression in Infix format:\t");
      scanf("%[^\n]s", infix_expression);
      expression_conversion();
      printf("\nExpression in Postfix Format: \t%s\n", postfix_expression);
      return 0;
}
 
void expression_conversion()//main function for conversion of expression
{
      unsigned int count, temp = 0;
      char next;
      char character; 
      for(count = 0; count < strlen(infix_expression); count++)
      {
            character = infix_expression[count];
            if(!check_space_tabs(character)) // controll goes inside if it is not a space
            {
                  switch(character)
                  {
                        case '(': push(character);
                                  break;
                        case ')':
                                  while((next = pop()) != '(')
                                  {
                                        postfix_expression[temp++] = next;
                                  }
                                  break;
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '%':
                        case '^':
                                  while(!isEmpty() && priority(stack[top]) >= priority(character))
                                  postfix_expression[temp++] = pop();
                                  push(character);
                                  break;
                        default: 
                                  postfix_expression[temp++] = character;
                  }
            }
      }
       //function to check for empty
      while(!isEmpty()) 
      {
            postfix_expression[temp++] = pop();
      }
      postfix_expression[temp] = '\0';
}
 //switing between priority of operators
int priority(char character)
{
      switch(character)
      {
            case '(': return 0;
            case '+':
            case '-':
                      return 1;
            case '*':
            case '/':
            case '%':
                      return 2;
            case '^':
                      return 3;
            default:
                      return 0;
      }
}
 //function for push operation
void push(long int character)
{
      if(top > 50)
      {
            printf("Stack Overflow\n");
            exit(1);
      }
      top = top + 1;
      stack[top] = character;
}
 //function for checking space betwwen exp
int check_space_tabs(char character)
{
      if(character == ' ' || character == '\t')
      {
            return 1;
      }
      else
      {
            return 0;
      }
}
 //function for pop
int pop()
{
      if(isEmpty())
      {
            printf("Stack is Empty\n");
            exit(1);
      }
      return(stack[top--]);
}
 //function to check empty
int isEmpty()
{
      if(top == -1)
      {
            return 1;
      }
      else
      {
            return 0;
      }
}
