// This C program implements a binary search tree (BST)
// and performs preorder, inorder, and postorder traversals using an iterative approach (with the help of stacks).
#include <stdio.h>
#include <stdlib.h> // Added for malloc

#define MAX 100 // Increased stack size
// NODE STructure
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} NODE;
// Stack Structure
typedef struct stack
{
    NODE *stack[MAX];
    int top;
} STACK;
// Adds a node to the stack
void push(NODE *t, STACK *s)
{
    if (s->top == MAX - 1)
    {
        printf("Stack Overflow\n");
    }
    else
    {
        s->stack[++(s->top)] = t;
    }
}
// Removes and returns the top node from the stack.
NODE *pop(STACK *s)
{
    if (s->top == -1)
    {
        printf("Stack Underflow\n");
        return NULL;
    }
    else
    {
        return s->stack[(s->top)--];
    }
}

NODE *createNode(int data)
{
    NODE *nn = (NODE *)malloc(sizeof(NODE));
    nn->data = data;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

int isEmpty(NODE *t)
{
    return (t == NULL);
}

NODE *insertNode(NODE *root, int data)
{
    if (isEmpty(root))
    {
        root = createNode(data);
    }
    else if (data <= root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else
    {
        root->right = insertNode(root->right, data);
    }
    return root;
}

void inorder(NODE *t)
{
    if (isEmpty(t))
    {
        printf("Tree is empty\n");
        return;
    }

    STACK *s = (STACK *)malloc(sizeof(STACK));
    s->top = -1;
    NODE *temp = NULL;

    do
    {
        while (t != NULL)
        { // traverse left
            push(t, s);
            t = t->left;
        }

        temp = pop(s);
        if (temp != NULL)
        {
            printf("%d ", temp->data);
            t = temp->right; // go to right tree
        }
    } while (t != NULL || s->top != -1);

    free(s); // Free the allocated stack memory
}
/*The stack ensures that nodes are processed in the correct order: push right first, then left,
 because the left subtree needs to be processed before the right subtree.*/
void preorder(NODE *t)
{
    if (isEmpty(t))
    {
        printf("Tree is empty\n");
        return;
    }

    STACK *s = (STACK *)malloc(sizeof(STACK));
    s->top = -1;
    push(t, s);

    while (s->top != -1)
    {
        NODE *temp = pop(s);
        printf("%d ", temp->data);

        if (temp->right != NULL)
        {
            push(temp->right, s);
        }
        if (temp->left != NULL)
        {
            push(temp->left, s);
        }
    }

    free(s); // Free the allocated stack memory
}
//(Left,Right,Root)
/*The algorithm uses two stacks (s1 and s2) to simulate a post-order traversal of a binary tree or bst:
s1 is used to traverse the tree (root, right, left).
s2 stores the nodes in a reverse order of the traversal (root, right, left),
So that when printed, it results in post-order traversal (left, right, root).*/
void postorder(NODE *t)
{
    if (isEmpty(t))
    {
        printf("Tree is empty\n");
        return;
    }
    STACK *s1 = (STACK *)malloc(sizeof(STACK));
    STACK *s2 = (STACK *)malloc(sizeof(STACK));
    s1->top = -1;
    s2->top = -1;
    NODE *temp = NULL;

    push(t, s1);
    while (s1->top != -1)
    {
        temp = pop(s1);
        push(temp, s2);

        if (temp->left != NULL)
        {
            push(temp->left, s1);
        }
        if (temp->right != NULL)
        {
            push(temp->right, s1);
        }
    }

    while (s2->top != -1)
    {
        temp = pop(s2);
        printf("%d ", temp->data);
    }

    free(s1); // Free the allocated stack memory
    free(s2);
}
int main()
{
    int n, d;
    NODE *root = NULL;
    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);

    printf("\nEnter the data: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &d);
        root = insertNode(root, d);
    }

    printf("\nPreorder traversal: ");
    preorder(root);
    printf("\nInorder traversal: ");
    inorder(root);
    printf("\nPostorder traversal: ");
    postorder(root);

    return 0;
}
