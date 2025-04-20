#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 10

typedef struct treeNode
{
    int utype;
    union
    {
        char operater;
        float operand;
    } u;
    struct treeNode *left;
    struct treeNode *right;
} NODE;

static int top = -1;

void push(NODE *nn, NODE *stack[])
{
    if (top < MAX - 1)
    { // Ensure we don't exceed the stack size
        stack[++top] = nn;
    }
    else
    {
        printf("STACK FULL\n");
    }
}

NODE *pop(NODE *stack[])
{
    if (top == -1)
    {
        printf("STACK EMPTY\n");
        return NULL; // Return NULL if stack is empty
    }
    return stack[top--];
}

NODE *construct(char exp[])
{
    NODE *nn, *stack[MAX]; // Use a pointer array for the stack
    int i = 0;

    while (exp[i])
    {
        if (isdigit(exp[i]))
        { // Operand case
            nn = (NODE *)malloc(sizeof(NODE));
            nn->utype = 1;
            nn->u.operand = exp[i] - '0'; // Convert to float directly for simplicity
            nn->left = NULL;
            nn->right = NULL;
            push(nn, stack);
        }
        else
        { // Operator case
            nn = (NODE *)malloc(sizeof(NODE));
            nn->utype = 2;
            nn->u.operater = exp[i];
            nn->right = pop(stack);
            nn->left = pop(stack);
            if (nn->right == NULL || nn->left == NULL)
            { // Check for invalid expression
                printf("Invalid expression\n");
                free(nn);
                return NULL;
            }
            push(nn, stack);
        }
        i++;
    }
    return pop(stack); // Final pop to get the root of the tree
}

void inorder(NODE *bst)
{
    if (bst != NULL)
    {
        inorder(bst->left);
        if (bst->utype == 1)
            printf("%g ", bst->u.operand);
        else
            printf("%c ", bst->u.operater);
        inorder(bst->right);
    }
}

float calculate(float x, char op, float y)
{
    float res;
    switch (op)
    {
    case '+':
        res = x + y;
        break;
    case '-':
        res = x - y;
        break;
    case '*':
        res = x * y;
        break;
    case '/':
        if (y != 0)
            res = x / y;
        else
        {
            printf("Division by zero error\n");
            exit(1); // Exit if division by zero
        }
        break;
    default:
        printf("Invalid operator\n");
        exit(1);
    }
    return res;
}

float evaluate(NODE *bst)
{
    if (bst->utype == 1)
        return bst->u.operand;
    float x = evaluate(bst->left);
    float y = evaluate(bst->right);
    return calculate(x, bst->u.operater, y);
}

int main()
{
    NODE *bst;
    char exp[MAX] = "567*+8-";
    bst = construct(exp);

    if (bst == NULL)
    {
        printf("Failed to construct tree\n");
        return 1;
    }

    printf("In-order traversal: ");
    inorder(bst);
    printf("\n");

    printf("Evaluation result: %g\n", evaluate(bst));
    return 0;
}
