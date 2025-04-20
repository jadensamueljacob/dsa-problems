#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} stack;

// Initialize the stack
void init_stk(stack *st) {
    st->top = -1;
}

// Push an element onto the stack
void push(stack *st, int value) {
    if (st->top == MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        st->data[++(st->top)] = value;
    }
}

// Pop an element from the stack
int pop(stack *st) {
    if (st->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    } else {
        return st->data[(st->top)--];
    }
}

// Check if the character is an operator
int isoper(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Evaluate the postfix expression
int postfix_eval(char* postfix) {
    int i = 0, result, op1, op2, a;
    char ch;
    stack st;
    init_stk(&st);

    while (postfix[i] != '\0') {
        ch = postfix[i];
        
        if (isoper(ch)) {  // If character is an operator
            op1 = pop(&st);
            op2 = pop(&st);
            
            switch (ch) {
                case '+': result = op2 + op1;
                          break;
                case '-': result = op2 - op1;
                          break;
                case '*': result = op2 * op1;
                          break;
                case '/': result = op2 / op1;
                          break;
            }
            push(&st, result);  // Push the result back to stack
        } else if (isdigit(ch)) {  // If character is a digit (operand)
            push(&st, ch - '0');  // Convert char to int and push
        } else {
            printf("Invalid character in expression\n");
            return -1;
        }
        i++;
    }
    return pop(&st);  // The final result
}

int main() {
    char postfix[MAX];

    printf("Enter a postfix expression: ");
    scanf("%s", postfix);

    int result = postfix_eval(postfix);
    printf("The result of the postfix expression is: %d\n", result);

    return 0;
}
