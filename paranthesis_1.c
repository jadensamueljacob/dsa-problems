/*Application of a Stack:
1. Infix to Postfix conversion
2. Evaluate a postfix expression
3. Check for balanced parenthesis
*/
//Check for balanced parenthesis
//{},(),[]
/*
(A+B) - Balanced parenthesis
{(A+B)+(c+d)} - Balanced parathesis

{(x+y)*(z) - not balanced
[2+a] + x ] - not balanced
Counting will not work.

)( - not balanced
[()()] - balanced
[(])

Last unclosed and the first closed will be matched


Pseudocode for checking the balanced parenthesis:

check_balanced_parenthesis(exp) //string
{
    n <- length(exp)
    create a stack s
    for i->0 till n-1
        if exp[i] is '(' or '[' or '{'
            push(exp[i]) to s
        else if exp[i] is ')' or ']' or '}'
            if(s is empty) || top does not pair with the exp[i])
                {
                return false
                }
        else
        {
        pop() - last unlcosed parenthesis is popped.
        }
    return s is empty?true:false
}
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100 // Maximum size of stack

// Stack structure
typedef struct stack  {
    char items[MAX];
    int top;
}stack;

// Function to initialize stack
void initStack(stack* S) {
    S->top = -1;
}

// Function to check if the stack is empty
int isEmpty(stack* S) {
    return S->top == -1;
}

// Function to push an element into the stack
void push(stack* S, char x) {
    if (S->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    S->items[++(S->top)] = x;
}

// Function to pop an element from the stack
char pop(stack* S) {
    if (isEmpty(S)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return S->items[(S->top)--];
}

// Function to return the top element of the stack
char topmost(stack* S) {
    if (!isEmpty(S)) {
        return S->items[S->top];
    }
    return '\0';
}

// Function to check whether two characters are opening and closing of the same type
int arePair(char opening, char closing) {
    if (opening == '(' && closing == ')') return 1;
    else if (opening == '{' && closing == '}') return 1;
    else if (opening == '[' && closing == ']') return 1;
    return 0;
}

// Function to check whether the parentheses are balanced
int check_balance(char* exp) {
    stack S;
    initStack(&S);

    for (int i = 0; i < strlen(exp); i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
            push(&S, exp[i]);
        } else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty(&S) || !arePair(topmost(&S), exp[i])) {
                return 0;
            } else {
                pop(&S);
            }
        }
    }

    return isEmpty(&S);
}

int main() {
    char expression[MAX];
    printf("Enter an expression: ");
    scanf("%s", expression);

    if (check_balance(expression)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return 0;
}
