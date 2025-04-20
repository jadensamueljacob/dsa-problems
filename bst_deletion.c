#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the binary search tree
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}NODE;

// Function to find the minimum value in a tree (used for case 3 in deletion)
NODE *FindMin(NODE *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a node with the given data from the binary search tree
NODE *Delete(NODE *root, int data)
{
    if (root == NULL)
        return root; // Base case: if the tree is empty, return NULL

    // Recursively find the node to be deleted
    if (data < root->data)
        root->left = Delete(root->left, data); // Go to the left subtree
    else if (data > root->data)
        root->right = Delete(root->right, data); // Go to the right subtree
    else
    {
        // Found the node to be deleted

        // Case 1: No child (leaf node)
        if (root->left == NULL && root->right == NULL)
        {
            free(root); // Delete the node
            root = NULL;
        }
        // Case 2: One child (right child exists)
        else if (root->left == NULL)
        {
            NODE *temp = root;
            root = root->right; // Set root to right child
            free(temp);         // Free memory of the original root
        }
        // Case 2: One child (left child exists)
        else if (root->right == NULL)
        {
            NODE *temp = root;
            root = root->left; // Set root to left child
            free(temp);        // Free memory of the original root
        }
        // Case 3: Two children
        else
        {
            NODE *temp = FindMin(root->right);      // Find the inorder successor (minimum in the right subtree)
            root->data = temp->data;                       // Replace the current node's data with successor's data
            root->right = Delete(root->right, temp->data); // Delete the inorder successor
        }
    }
    return root;
}

// Function to visit and print nodes in inorder (left, root, right)
void Inorder(NODE *root)
{
    if (root == NULL)
        return;

    Inorder(root->left);       // Visit left subtree
    printf("%d ", root->data); // Print current node's data
    Inorder(root->right);      // Visit right subtree
}

// Function to insert a new node with given data into the binary search tree
NODE *Insert(NODE *root, int data)
{
    if (root == NULL)
    {
        // Create a new node if the root is NULL (empty tree)
        NODE *newNode = (NODE *)malloc(sizeof(NODE));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    else if (data <= root->data)
        root->left = Insert(root->left, data); // Insert in the left subtree if data is smaller or equal
    else
        root->right = Insert(root->right, data); // Insert in the right subtree if data is greater

    return root;
}

int main()
{

    NODE *root = NULL;
   
    root = Insert(root, 20);
    root = Insert(root, 16);
    root = Insert(root, 28);
    root = Insert(root, 15);
    root = Insert(root, 18);
    root = Insert(root, 14);
    root = Insert(root, 17);
    root = Insert(root, 19);
    root = Insert(root, 22);
    root = Insert(root, 21);
    root = Insert(root, 30);
    root = Insert(root, 39);

    // Deleting node with value 5
    //root = Delete(root, 5);
    //root = Delete(root, 4);
     root = Delete(root, 21);

    // Print nodes in inorder traversal after deletion
    printf("Inorder traversal: ");
    Inorder(root);
    printf("\n");

    return 0;
}
