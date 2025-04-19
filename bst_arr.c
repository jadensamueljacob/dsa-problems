#include <stdio.h>
#define SIZE 10

typedef struct node
{
    int data;
    int flag;
} NODE;

void insert(NODE *bst, int data, int index)
{
    if (bst[index].flag == 0 && index < SIZE)
    { // exit criteria
        bst[index].data = data;
        bst[index].flag = 1;
    }
    else if (data < bst[index].data && index < SIZE)
    {
        index = 2 * index + 1; // left child
        insert(bst, data, index);
    }
    else if (data > bst[index].data && index < SIZE)
    {
        index = 2 * index + 2; // right child
        insert(bst, data, index);
    }
    else
        printf("\nInsertion is NOT possible.");
}
void inorder(NODE *bst, int i)
{
    if (bst[i].flag == 1 && i < SIZE)
    {
        inorder(bst, 2 * i + 1); // left subtree
        printf("%d ", bst[i].data);
        inorder(bst, 2 * i + 2); // right subtree
    }
}
int main()
{
    int ch, data;
    NODE bst[SIZE] = {}; // initialize flag as zero
    // Inserting the data
    do
    {
        printf("\nEnter the data:");
        scanf("%d", &data);
        insert(bst, data, 0);
        printf("\nPress 0 to discontinue:");
        scanf("%d", &ch);
    } while (ch);
    // Inorder traversal
    inorder(bst, 0);
    return 0;
}
