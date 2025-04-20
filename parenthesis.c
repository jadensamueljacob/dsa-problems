#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a simple stack structure
typedef struct Stack {
    char* data;
    int top;
    int maxSize;
} Stack;

Stack* createStack(int maxSize) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (char*)malloc(maxSize * sizeof(char));
    stack->top = -1;
    stack->maxSize = maxSize;
    return stack;
}

bool isFull(Stack* stack) {
    return stack->top == stack->maxSize - 1;
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char item) {
    if (!isFull(stack)) {
        stack->data[++stack->top] = item;
    }
}

char pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return '\0'; // Return null character if stack is empty
}

char peek(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return '\0';
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') || 
           (open == '{' && close == '}') || 
           (open == '[' && close == ']');
}

bool areParenthesesBalanced(char* expression) {
    Stack* stack = createStack(100); // Create stack of sufficient size

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(stack, ch); // Push opening parenthesis to stack
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(stack) || !isMatchingPair(pop(stack), ch)) {
                return false; // Mismatch found
            }
        }
    }

    bool balanced = isEmpty(stack); // Stack should be empty if balanced
    free(stack->data);
    free(stack);
    return balanced;
}

int main() {
    char expression[100];
    printf("Enter an expression: ");
    scanf("%s", expression);

    if (areParenthesesBalanced(expression)) {
        printf("Parentheses are balanced.\n");
    } else {
        printf("Parentheses are not balanced.\n");
    }

    return 0;
}
