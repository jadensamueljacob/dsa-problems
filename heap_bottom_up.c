#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i;      // Initialize largest as root
    int left = 2 * i;     // Left child (1-based index: 2*i)
    int right = 2 * i + 1;// Right child (1-based index: 2*i + 1)

    // If left child is larger than root
    if (left <= n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right <= n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        // Swap
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n) {
    // Index of the last non-leaf node in 1-based array
    int startIdx = n / 2;

    // Perform reverse level order traversal from last non-leaf node
    // and heapify each node
    for (int i = startIdx; i >= 1; i--) {
        heapify(arr, n, i);
    }
}

// A utility function to print the array representation of the heap
void printArray(int arr[], int n) {
    for (int i = 1; i <= n; ++i)  // Start printing from index 1
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    // Create an array with a dummy element at index 0
    int arr[] = {0, 4, 1, 3, 2, 1000}; // 0th index ignored
    int n = 5; // Actual size of the heap (excluding the 0th index)

    buildHeap(arr, n);

    printf("Heap constructed using bottom-up approach:\n");
    printArray(arr, n);

    return 0;
}
