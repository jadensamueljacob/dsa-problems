#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 20

typedef struct heap
{
    int heap[SIZE];
    int heapsize;
} HEAP;

// Initialize the heap
void init(HEAP *h)
{
    h->heapsize = 0;       // Start with an empty heap
    h->heap[0] = INT_MAX;  // Max value at index 0 to simplify comparisons
    //Index 0 (h->heap[0] = INT_MAX) is a placeholder, simplifying comparisons 
    //during heap operations by ensuring the root at index 1 never bubbles up. 
    //It isn't used in the actual heap operations
}

// Swap two elements in the heap
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert an element into the heap (Top-down approach)
//insert element one by one
void insert(HEAP *h, int data)
{
    int current, parent;
    h->heap[++(h->heapsize)] = data;  // Insert the element at the end
    current = h->heapsize;
    parent = current / 2;

    // Bubble up: Move the inserted element up to maintain max-heap property
    while (h->heap[parent] < h->heap[current] && current > 1)
    {
        swap(&h->heap[parent], &h->heap[current]);
        current = parent;
        parent = current / 2;
    }
}

// Display the heap elements
void display(HEAP *h)
{
    printf("Heap: ");
    for (int i = 1; i <= h->heapsize; i++)
    {
        printf("%d ", h->heap[i]);
    }
    printf("\n");
}

// Delete the root (maximum element) from the heap
int deleteMax(HEAP *h)
{
    int max = h->heap[1];  // The root is the maximum element
    h->heap[1] = h->heap[h->heapsize--];  // Move the last element to the root
    int current = 1;
    int child = 2 * current;

    // Bubble down: Restore heap property by moving the root element down
    while (child <= h->heapsize)
    {
        // Select the larger child
        if (child + 1 <= h->heapsize && h->heap[child + 1] > h->heap[child])
        {
            child++;
        }

        // If the current element is smaller than the larger child, swap them
        if (h->heap[current] < h->heap[child])
        {
            swap(&h->heap[current], &h->heap[child]);
            current = child;
            child = 2 * current;
        }
        else
        {
            break;
        }
    }

    return max;
}

int main()
{
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    init(heap);

    int data, choice;

    // Insert elements into the heap
    do
    {
        printf("Enter data to insert into heap: ");
        scanf("%d", &data);
        insert(heap, data);

        printf("Heap after insertion: ");
        display(heap);

        printf("Press 1 to continue inserting, 0 to stop: ");
        scanf("%d", &choice);
    } while (choice == 1);

    // Display the final heap
    printf("\nFinal Heap: ");
    display(heap);

    // Delete elements from the heap (priority queue simulation)
    printf("\nDeleting elements from heap (Priority Queue): ");
    /*while (heap->heapsize > 0)
    {
        printf("%d ", deleteMax(heap));  // Delete the max element and print it
    }
    printf("\n");*/
    //printf("%d ", deleteMax(heap));
    //printf("\nHeap After deleting:");
    //display(heap);

    printf("\nPRIORITY QUEUE - MAX HEAP:\n");
    if (heap->heapsize >= 1)
    {
        int n = heap->heapsize;
        for (int i = 1; i <= n; i++)
            printf("%d ", deleteMax(heap));
             printf("\n");
    }
    // Free allocated memory
   free(heap);

    return 0;
}
