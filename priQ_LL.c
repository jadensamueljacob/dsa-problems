#include <stdio.h>
#include <stdlib.h>

// Node structure to represent each element in the priority queue
typedef struct Node {
    int data; // Data stored in the node
    int priority; // Priority of the node
    struct Node* next; // Pointer to the next node
}NODE;

// PriorityQueue structure to represent the front of the priority queue
typedef struct priQ {
    NODE* front; // Pointer to the front (head) of the priority queue
}PQ;



// Function to create an empty priority queue
PQ* createPriorityQueue() {
    PQ* pq = (PQ*)malloc(sizeof(PQ));
    pq->front = NULL;
    return pq;
}

// Function to check if the priority queue is empty
int isEmpty(PQ* pq) {
    return pq->front == NULL;
}

// Function to create a new node with given data and priority
NODE* createNode(int data, int priority) {
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = data;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}

// Function to insert a new node into the priority queue based on its priority
void enqueue(PQ* pq, int data, int priority) {
    NODE* temp = createNode(data, priority);

    // If the queue is empty or the new node has higher priority than the front node
    if (isEmpty(pq) || pq->front->priority > priority) {
        temp->next = pq->front;
        pq->front = temp;
    } else {
        // Traverse the queue and find the correct position to insert the new node
        NODE* p = pq->front;
        while (p->next != NULL && p->next->priority <= priority) {
            p = p->next;
        }
        temp->next = p->next;
        p->next = temp;
    }
}

// Function to remove and return the highest priority element from the priority queue
int dequeue(PQ* pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty.\n");
        return -1;
    }

    // Remove the front node (highest priority node)
    NODE* temp = pq->front;
    pq->front = pq->front->next;
    int data = temp->data;
    free(temp);
    return data;
}

// Function to display the elements of the priority queue
void display(PQ* pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty.\n");
        return;
    }

    NODE* p = pq->front;
    printf("Priority Queue: ");
    while (p != NULL) {
        printf("%d (Priority: %d) -> ", p->data, p->priority);
        p = p->next;
    }
    printf("NULL\n");
}

int main() {
    // Create an empty priority queue
    PQ* pq = createPriorityQueue();

    // Insert elements into the priority queue
    enqueue(pq, 4, 1);
    enqueue(pq, 5, 2);
    enqueue(pq, 6, 0);
    enqueue(pq, 7, 1);

    // Display the elements of the priority queue
    display(pq);

    // Remove elements from the priority queue
    printf("Dequeued: %d\n", dequeue(pq));
    printf("Dequeued: %d\n", dequeue(pq));

    // Display the remaining elements
    display(pq);

    return 0;
}
