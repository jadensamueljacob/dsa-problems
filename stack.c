#include<stdio.h>
#include<stdlib.h>

int *stack, i, n, x, top;

void push() 
{
    if (top >= n - 1) 
    {
        printf("Stack overflow\n");
    } else 
    {
        printf("Enter the element to be inserted: ");
        scanf("%d", &x);
        top++;
        stack[top] = x;
    }
}

void pop() 
{
    if (top <= -1) 
    {
        printf("Stack is underflow\n");
    } else 
    {
        printf("The deleted element is %d\n", stack[top]);
        top--;
    }
}

void peek() 
{  
    if (top >= 0) 
    {
        printf("The top element is %d\n", stack[top]);
    } else 
    {
        printf("Stack is empty\n");
    }
}

void display() 
{
    if (top >= 0) 
    {
        printf("The elements in the stack are: ");
        for (int i = top; i >= 0; i--) 
        {
            printf("%d ", stack[i]);
        }
        printf("\n");
    } else {
        printf("Stack is empty\n");
    }
}

int main() 
{
    top = -1; // Initialize stack as empty
    int choice;
    printf("Enter the size of the stack: ");
    scanf("%d", &n);

    // Dynamic memory allocation
    stack = (int*)malloc(n * sizeof(int));
    if (stack == NULL) 
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("Stack operations:\n1) Push\n2) Pop\n3) Peek\n4) Display\n5) Exit\n");
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice\n");
        }
    } while (choice != 5);

    free(stack);
    return 0;
}
