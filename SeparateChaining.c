#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node {
    int data;
    struct node *next;
} NODE;

typedef struct hashtable {
    int count;
    struct node *head;
} HASHTABLE;

// Function to create a new node
NODE* createNode(int key) {
    NODE *nn = (NODE*)malloc(sizeof(NODE));
    if (!nn) {
        printf("Memory allocation error\n");
        exit(1);
    }
    nn->data = key;
    nn->next = NULL;
    return nn;
}

// Insert key into the hash table
void insert(int key, HASHTABLE *HashTable) {
    int hash = key % SIZE; // k mod n ; n here is the size
    NODE *nn = createNode(key);
    nn->next = HashTable[hash].head;
    HashTable[hash].head = nn;
    HashTable[hash].count++;
}

// Search for a key in the hash table
void search(int key, HASHTABLE *HashTable) {
    int hash = key % SIZE, pos = 1;
    NODE *t = HashTable[hash].head;
    while (t) {
        if (t->data == key) {
            printf("\nElement found at index [%d], position [%d]\n", hash, pos);
            return;
        }
        t = t->next;
        pos++;
    }
    printf("\nData not found\n");
}

// Delete a key from the hash table
void deleteData(int key, HASHTABLE *HashTable) {
    int hash = key % SIZE;
    NODE *t = HashTable[hash].head, *prev = NULL;
    while (t) {
        if (t->data == key) {
            if (prev) {
                prev->next = t->next;
            } else {
                HashTable[hash].head = t->next;
            }
            free(t);
            HashTable[hash].count--;
            printf("\nData deleted successfully\n");
            return;
        }
        prev = t;
        t = t->next;
    }
    printf("\nData not found\n");
}

// Display the hash table contents
void display(HASHTABLE *HashTable) {
    for (int i = 0; i < SIZE; i++) {
        if (HashTable[i].count != 0) {
            printf("\nindex [%d]: ", i);
            NODE *t = HashTable[i].head;
            while (t) {
                printf("%d -> ", t->data);
                t = t->next;
            }
            printf("NULL");
        }
    }
    printf("\n");
}

// Main function to initialize the hash table and test the operations
int main() {
    HASHTABLE HashTable[SIZE] = {0}; // Initialize the hash table with zero counts and NULL heads
    insert(10, HashTable);
    insert(20, HashTable);
    insert(15, HashTable);
    insert(30, HashTable);
    insert(47, HashTable);
    insert(65, HashTable);
    //insert(60, HashTable);
    display(HashTable);
    search(20, HashTable);
    deleteData(10, HashTable);
    display(HashTable);
    return 0;
}
