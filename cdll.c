#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next, *prev;
};

typedef struct node node_t;

struct dlist {
    node_t *head;
};

typedef struct dlist dlist_t;

void insert_head(dlist_t*, int);
void insert_tail(dlist_t*, int);
void delete_node(dlist_t*, int);
void display(dlist_t*);
void init_list(dlist_t*);

int main() {
    int ch, x;
    dlist_t dl;

    init_list(&dl);

    while (1) { 
        printf("\n");
        display(&dl);
        printf("\n1..Insert Head\n");
        printf("2..Insert Tail\n");
        printf("3..Delete a Node..\n");
        printf("4..Display\n");
        printf("5..Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the number: ");
                scanf("%d", &x);
                insert_head(&dl, x);
                break;
            case 2:
                printf("Enter the number: ");
                scanf("%d", &x);
                insert_tail(&dl, x);
                break;
            case 3:
                printf("Enter the value of the node to be deleted: ");
                scanf("%d", &x);
                delete_node(&dl, x);
                break;
            case 4:
                display(&dl);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void init_list(dlist_t* ptr_list) {
    ptr_list->head = NULL;
}

void insert_head(dlist_t* dl, int data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = data;
    if (dl->head == NULL) {
        new_node->next = new_node->prev = new_node;
        dl->head = new_node;
    } else {
        node_t* tail = dl->head->prev;
        new_node->next = dl->head;
        new_node->prev = tail;
        tail->next = new_node;
        dl->head->prev = new_node;
        dl->head = new_node;
    }
}

void insert_tail(dlist_t* dl, int data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = data;
    if (dl->head == NULL) {
        new_node->next = new_node->prev = new_node;
        dl->head = new_node;
    } else {
        node_t* tail = dl->head->prev;
        new_node->next = dl->head;
        new_node->prev = tail;
        tail->next = new_node;
        dl->head->prev = new_node;
    }
}

void delete_node(dlist_t* dl, int data) {
    if (dl->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    node_t* current = dl->head;
    node_t* prev_node = NULL;

    // Find the node with the given data
    do {
        if (current->data == data) {
            if (current->next == current && current->prev == current) { // Only one node
                dl->head = NULL;
            } else {
                node_t* next_node = current->next;
                prev_node = current->prev;
                prev_node->next = next_node;
                next_node->prev = prev_node;
                if (current == dl->head) {
                    dl->head = next_node;
                }
            }
            free(current);
            printf("Node deleted successfully.\n");
            return;
        }
        current = current->next;
    } while (current != dl->head);

    printf("Node not found.\n");
}

void display(dlist_t* dl) {
    if (dl->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    node_t* current = dl->head;
    printf("Circular Doubly Linked List: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != dl->head);
    printf("\n");
}

 