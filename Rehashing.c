#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
typedef struct node {
    int data;
    int flag; // 0: empty, 1: occupied
} NODE;

typedef struct {
    int size;
    struct node *hashTable;
} HASH;

int count = 0; // Initialize count

HASH *createHash(int size) {
    HASH *hash = (HASH *)malloc(sizeof(HASH));
    hash->size = size;
    hash->hashTable = (NODE *)malloc(size * sizeof(NODE));
    for (int i = 0; i < size; i++) {
        hash->hashTable[i].flag = 0; // Set all nodes as empty
    }
    return hash;
}

void destroyHash(HASH *hash) {
    free(hash->hashTable);
    free(hash);
}

void rehash(int key, HASH **h) {
    int newSize = (*h)->size * 2;
    HASH *newHash = createHash(newSize);

    for (int i = 0; i < (*h)->size; i++) {
        if ((*h)->hashTable[i].flag == 1) {
            int hash, j = 0;
            hash = ((*h)->hashTable[i].data % newSize + j) % newSize;
            while (newHash->hashTable[hash].flag != 0) {
                j++;
                hash = ((*h)->hashTable[i].data % newSize + j) % newSize;
            }
            newHash->hashTable[hash].data = (*h)->hashTable[i].data;
            newHash->hashTable[hash].flag = 1;
        }
    }

    destroyHash(*h);
    *h = newHash;
}

void insert_(int key, HASH *h) {
    int hash, i = 0;
    count++;
    if (count > (float)(0.75 * h->size)) {
        rehash(key, &h);
    } else {
        hash = ((key % h->size) + i) % h->size;
        while (h->hashTable[hash].flag != 0) {
            i++;
            hash = ((key % h->size) + i) % h->size;
        }
        h->hashTable[hash].data = key;
        h->hashTable[hash].flag = 1;
        printf("The data %d is inserted\n", key);
    }
}

// Display the hash table contents
void display(HASH *h) {
    printf("\nHash Table:\n");
    for (int i = 0; i < h->size; i++) {
        if (h->hashTable[i].flag == 1) {
            printf("Index %d: %d\n", i, h->hashTable[i].data);
        } else {
            printf("Index %d: EMPTY\n", i);
        }
    }
    printf("\n");
}
void search(int key, HASH *h) {
    int hash, i = 0;
    hash = (key % h->size + i) % h->size;
    while (i < h->size) {
        if (h->hashTable[hash].data == key && h->hashTable[hash].flag == 1) {
            printf("\nThe data %d is found at index %d\n", key, hash);
            return;
        }
        i++;
        hash = (key % h->size + i) % h->size;
    }
    printf("\nData not found\n");
}

int main() {
    HASH *hashTable = createHash(SIZE);

    // Test insertions with rehashing
    insert_(5, hashTable);
    insert_(15, hashTable);
    insert_(25, hashTable);
    insert_(35, hashTable);
    display(hashTable);

    // Test searching
    search(15, hashTable); // Should find the data
    search(35, hashTable); // Should find the data
    search(45, hashTable); // Should not find the data

    return 0;
}
