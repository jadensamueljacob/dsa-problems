#include <stdio.h>
#include <stdlib.h>

// Define the structure for linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of the linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to concatenate two linked lists
struct Node* concatenateLists(struct Node* head1, struct Node* head2) 
{
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct Node* temp = head1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head2;

    return head1;
}

// Function to print a linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    int n1, n2, data, i;

    // Taking input for first linked list
    printf("Enter the number of elements for the first list: ");
    scanf("%d", &n1);
    printf("Enter the elements:\n");
    for (i = 0; i < n1; i++) {
        scanf("%d", &data);
        insertAtEnd(&list1, data);
    }

    // Taking input for second linked list
    printf("Enter the number of elements for the second list: ");
    scanf("%d", &n2);
    printf("Enter the elements:\n");
    for (i = 0; i < n2; i++) {
        scanf("%d", &data);
        insertAtEnd(&list2, data);
    }

    // Print both lists
    printf("First List: ");
    printList(list1);
    printf("Second List: ");
    printList(list2);

    // Concatenate the two lists
    struct Node* concatenatedList = concatenateLists(list1, list2);

    // Print concatenated list
    printf("Concatenated List: ");
    printList(concatenatedList);

    return 0;
}
