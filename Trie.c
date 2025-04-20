#include <stdio.h>
#include <stdlib.h>

// Define the structure for a Trie node with child nodes and an end-of-string (eos) marker
struct trie
{
    struct trie *child[255]; // Array of pointers to child nodes for each character
    int eos;                 // End-of-string flag to mark the end of a word
};

// Define a stack structure to aid in deletion by storing nodes and indices
struct stack
{
    struct trie *node; // Pointer to a Trie node
    int index;         // Character index for backtracking during deletion
};

typedef struct stack Stack;
char output[30];       // Array to store current word during traversal (for display)
int len = 0, top = -1; // `len` is current word length, `top` is stack top index
Stack *STACK[30];      // Stack to store Trie nodes and their indices for deletion
typedef struct trie Trie;

// Push a Trie node and its index onto the stack
void push(Trie *t, int index)
{
    Stack *nn = (Stack *)malloc(sizeof(Stack)); // Create a new stack element
    nn->node = t;
    nn->index = index;
    STACK[++top] = nn; // Push the element onto the stack
}

// Pop a stack element to backtrack during deletion
Stack *pop()
{
    return STACK[top--]; // Pop the top element and decrement the stack pointer
}

// Count the number of children for a given Trie node (used to check if node can be deleted)
int ChildCount(Trie *t)
{
    int count = 0;
    for (int i = 0; i < 256; i++) // Iterate through all possible child nodes
    {
        if (t->child[i] != NULL) // If child node exists, increment count
            count++;
    }
    return count;
}

// Create and initialize a new Trie node
Trie *createNode()
{
    Trie *nn = (Trie *)malloc(sizeof(Trie)); // Allocate memory for a new Trie node
    for (int i = 0; i < 255; i++)            // Initialize all child pointers to NULL
        nn->child[i] = NULL;
    nn->eos = 0; // Set end-of-string marker to 0 (not end of a word)
    return nn;
}

// Insert a word into the Trie
void insertWord(char *word, Trie *root)
{
    int index;
    Trie *t = root;
    for (int i = 0; word[i] != '\0'; i++) // Traverse through each character in the word
    {
        index = word[i];             // Use ASCII value as index to handle full character set
        if (t->child[index] == NULL) // If no node exists for this character, create one
            t->child[index] = createNode();
        t = t->child[index]; // Move to the child node
    }
    t->eos = 1; // Mark the end of the word at the last node
}

// Display all words in the Trie
void display(Trie *root)
{
    Trie *t = root;
    for (int i = 0; i < 255; i++) // Traverse all possible children for each character
    {
        if (t->child[i] != NULL) // If a child node exists
        {
            output[len++] = i;         // Add character to output array (current word)
            if (t->child[i]->eos == 1) // If this node marks the end of a word, print the word
            {
                printf("\n");
                for (int j = 0; j < len; j++)
                    printf("%c", output[j]);
            }
            display(t->child[i]); // Recursively display words starting from this node
        }
    }
    len--; // Backtrack to previous character after traversing child nodes
    return;
}

// Search for a word in the Trie
void search(char *word, Trie *root)
{
    int index;
    Trie *t = root;
    for (int i = 0; word[i] != '\0'; i++) // Traverse each character in the word
    {
        index = word[i];
        if (t->child[index] == NULL) // If character path doesn't exist, word is not found
        {
            printf("\nData not found");
            return;
        }
        t = t->child[index]; // Move to the next child node
    }
    if (t->eos == 1) // If end-of-string flag is set, word is found
        printf("\nData found");
    else
        printf("\nData not found"); // If end-of-string flag is not set, word does not exist
    return;
}

// Delete a word from the Trie
void deleteData(char *word, Trie *root)
{
    int index;
    Stack *s;
    Trie *t = root;
    for (int i = 0; word[i] != '\0'; i++) // Traverse each character in the word
    {
        index = word[i];
        if (t->child[index] == NULL) // If character path doesn't exist, word not found
        {
            printf("\nData not found");
            return;
        }
        push(t, index);      // Push the node and index to stack for backtracking
        t = t->child[index]; // Move to the child node
    }
    t->eos = 0; // Unset end-of-string to "remove" word

    if (ChildCount(t) >= 1) // If node has children, stop deletion here
        return;
    else // If no children, backtrack and delete nodes
    {
        s = pop(); // Get last visited node and index
        t = s->node;
        index = s->index;
        while (ChildCount(t) <= 1 && t->eos == 0) // Delete nodes until a branch or another word is encountered
        {
            free(t->child[index]);  // Free the child node
            t->child[index] = NULL; // Set pointer to NULL to remove reference
            s = pop();              // Move back to the previous node and repeat if necessary
            t = s->node;
            index = s->index;
        }
    }
}

void main()
{
    Trie *root;
    int ch;
    char word[30];
    root = createNode(); // Initialize root of Trie
    do
    {
        // Menu-driven interface for inserting, displaying, searching, and deleting words
        printf("\nEnter your choice 1.Insert 2.Display 3.Search 4. Delete 5.exit:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\nEnter the word to be inserted:");
            scanf("%s", word);
            insertWord(word, root); // Call insert function to add word to Trie
            break;
        case 2:
            len = 0;
            display(root); // Call display function to print all words in the Trie
            break;
        case 3:
            printf("\nEnter the word to be searched:");
            scanf("%s", word);
            search(word, root); // Call search function to find word in the Trie
            break;
        case 4:
            printf("\nEnter the word to be deleted:");
            scanf("%s", word);
            deleteData(word, root); // Call delete function to remove word from the Trie
            break;
        default:
            return; // Exit the program if choice is not valid
        }
    } while (ch); // Continue until exit option is chosen
}
