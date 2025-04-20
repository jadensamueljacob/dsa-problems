//Program for double eneded Queue using doubly linked list
#include <stdlib.h>
#include <stdio.h>

// Define the structure of a node in the doubly linked list
struct node {
    int key;                 // Data stored in the node
    struct node *next, *prev; // Pointers to the next and previous nodes
};

typedef struct node NODE;    // Alias for struct node

// Define the structure of the dequeue (double-ended queue)
struct dequeue {
    NODE *front;  // Pointer to the front node of the deque
    NODE *rear;   // Pointer to the rear node of the deque
};

typedef struct dequeue DEQ;  // Alias for struct dequeue

// Function declarations
void qdisplay(DEQ *);                // Display the contents of the deque
void qinsert_head(DEQ *, int);       // Insert a node at the head (front) of the deque
void qinsert_tail(DEQ *, int);       // Insert a node at the tail (rear) of the deque
int qdelete_head(DEQ *);             // Delete a node from the head of the deque
int qdelete_tail(DEQ *);             // Delete a node from the tail of the deque
void init(DEQ *p);                   // Initialize the deque

int main() {
    int k, x, ch;
    DEQ dq;
    init(&dq);  // Initialize the deque to be empty

    // Main loop to provide options for inserting, deleting, and displaying the deque
    while (1) {
        // Menu options for the user
        printf("\n1..Insert Head");
        printf("\n2..Insert Tail");
        printf("\n3..Delete Head");
        printf("\n4..Delete Tail");
        printf("\n5..Display");
        printf("\n6..EXIT");
        scanf("%d", &ch);

        // Switch case to handle the user's choice
        switch (ch) {
        case 1:
            printf("Enter the value: ");
            scanf("%d", &x);
            qinsert_head(&dq, x);  // Insert at the head
            break;
        case 2:
            printf("Enter the value: ");
            scanf("%d", &x);
            qinsert_tail(&dq, x);  // Insert at the tail
            break;
        case 3:
            k = qdelete_head(&dq);  // Delete from the head
            if (k >= 0)
                printf("Element deleted = %d\n", k);
            break;
        case 4:
            k = qdelete_tail(&dq);  // Delete from the tail
            if (k >= 0)
                printf("Element deleted = %d\n", k);
            break;
        case 5:
            qdisplay(&dq);  // Display the deque
            break;
        case 6:
            exit(0);  // Exit the program
        }
    }
}

// Initialize the deque
void init(DEQ *p) 
{
    p->front = p->rear = NULL;  // Set both front and rear to NULL (empty deque)
}

// Insert a node at the head (front) of the deque
void qinsert_head(DEQ *p, int x) 
{
    NODE *temp;

    // Create a new node
    temp = (NODE *)malloc(sizeof(NODE));
    temp->key = x;
    temp->next = temp->prev = NULL;  // Initialize the node's next and prev to NULL

    // If deque is empty, set both front and rear to the new node
    if (p->front == NULL)
        p->front = p->rear = temp;
    else {
        temp->next = p->front;  // Link the new node's next to the current front
        p->front->prev = temp;  // Link the current front's prev to the new node
        p->front = temp;        // Update front to the new node
    }
}

// Insert a node at the tail (rear) of the deque
void qinsert_tail(DEQ *p, int x) {
    NODE *temp;

    // Create a new node
    temp = (NODE *)malloc(sizeof(NODE));
    temp->key = x;
    temp->next = temp->prev = NULL;  // Initialize the node's next and prev to NULL

    // If deque is empty, set both front and rear to the new node
    if (p->front == NULL)
        p->front = p->rear = temp;
    else {
        p->rear->next = temp;  // Link the current rear's next to the new node
        temp->prev = p->rear;  // Link the new node's prev to the current rear
        p->rear = temp;        // Update rear to the new node
    }
}

// Delete a node from the tail (rear) of the deque
int qdelete_tail(DEQ *p) {
    NODE *pres;
    int key;

    // Check if deque is empty
    if (p->rear == NULL) {
        printf("Dequeue is empty\n");
        return -1;
    }

    pres = p->rear;  // Current rear node
    key = pres->key; // Store the key to return after deletion

    // If only one node exists, set both front and rear to NULL
    if (p->front == p->rear)
        p->front = p->rear = NULL;
    else {
        p->rear = pres->prev;  // Move the rear pointer to the previous node
        p->rear->next = NULL;  // Update the new rear's next pointer
    }
    free(pres);  // Free the deleted node
    return key;  // Return the deleted value
}

// Delete a node from the head (front) of the deque
int qdelete_head(DEQ *p) {
    NODE *pres;
    int key;

    // Check if deque is empty
    if (p->front == NULL) {
        printf("Dequeue is empty\n");
        return -1;
    }

    pres = p->front;  // Current front node
    key = pres->key;  // Store the key to return after deletion

    // If only one node exists, set both front and rear to NULL
    if (p->front == p->rear)
        p->front = p->rear = NULL;
    else {
        p->front = pres->next;  // Move the front pointer to the next node
        p->front->prev = NULL;  // Update the new front's prev pointer
    }
    free(pres);  // Free the deleted node
    return key;  // Return the deleted value
}

// Display the contents of the deque
void qdisplay(DEQ *p) {
    NODE *pres;

    // Check if deque is empty
    if (p->front == NULL)
        printf("Empty Dequeue\n");
    else {
        pres = p->front;  // Start from the front

        // Traverse the deque and print each node's key
        while (pres != p->rear) {
            printf("%d<->", pres->key);
            pres = pres->next;
        }
        printf("%d\n", pres->key);  // Print the last node
    }
}
