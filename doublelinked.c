#include <stdio.h>
#include <stdlib.h>
// count search concatenate insertatposition (sorting not in syllabus) 7 different operations totally
struct node 
{
    int data;
    struct node *prev, *next;
};

struct node *head = NULL;

struct node* create_node(int value) 
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (!newnode) 
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newnode->data = value;
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}

void insert_front(struct node **head, int value) 
{
    struct node *newnode = create_node(value);
    if (!newnode) 
        return;

    newnode->next = *head;

    if (*head != NULL) 
    {
        (*head)->prev = newnode;
    }

    *head = newnode;
}

void delete_front(struct node **head) 
{
    if (*head == NULL) 
    {
        printf("The list is empty, deletion is not possible\n");
        return;
    }

    struct node *current = *head;
    *head = (*head)->next;

    if (*head != NULL) 
    {
        (*head)->prev = NULL;
    }

    free(current);
}

void insert_end(struct node **head, int value) 
{
    struct node *newnode = create_node(value);
    if (!newnode) 
        return;

    if (*head == NULL) 
    {
        *head = newnode;
        return;
    }

    struct node *current = *head;
    while (current->next != NULL) 
    {
        current = current->next;
    }

    current->next = newnode;
    newnode->prev = current;
}

void delete_end(struct node **head) 
{
    if (*head == NULL) 
    {
        printf("List is empty, we cannot delete\n");
        return;
    }

    struct node *current = *head;
    while (current->next != NULL) 
    {
        current = current->next;
    }

    printf("The deleted element is %d\n", current->data);

    if (current->prev != NULL) 
    {
        current->prev->next = NULL;
    } 
    else 
    {
        *head = NULL;
    }

    free(current);
}

void display(struct node *head) 
{
    if (head == NULL) 
    {
        printf("The list is empty\n");
        return;
    }

    struct node *temp = head;
    while (temp != NULL) 
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

struct node* search(struct node *head, int value) 
{
    struct node *current = head;
    while (current != NULL) 
    {
        if (current->data == value) 
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int count(struct node *head, int value) 
{
    int count = 0;
    struct node *current = head;
    while (current != NULL) 
    {
        if (current->data == value) 
        {
            count++;
        }
        current = current->next;
    }
    return count;
}

void insert_at_position(struct node **head, int value, int position) 
{
    struct node *newnode = create_node(value);
    if (!newnode) 
        return;

    if (position <= 0) 
    {
        printf("Invalid position\n");
        free(newnode);
        return;
    }

    if (*head == NULL || position == 1) 
    {
        newnode->next = *head;
        if (*head != NULL) 
        {
            (*head)->prev = newnode;
        }
        *head = newnode;
        return;
    }

    struct node *current = *head;
    int count = 1;

    while (current->next != NULL && count < position - 1) 
    {
        current = current->next;
        count++;
    }

    newnode->next = current->next;
    newnode->prev = current;

    if (current->next != NULL) 
    {
        current->next->prev = newnode;
    }

    current->next = newnode;
}

int main() 
{
    int value, choice, position;
    struct node *found;

    while (1) 
    {
        printf("Enter your choice:\n1) Insert at front\n2) Delete from front\n3) Display\n4) Insert at end\n5) Delete from end\n6) Search for an element\n7) Count occurrences of an element\n8) Insert at a specific position\n9) Exit\n");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert_front(&head, value);
                break;
            case 2:
                delete_front(&head);
                break;
            case 3:
                display(head);
                break;
            case 4:
                printf("Enter value: ");
                scanf("%d", &value);
                insert_end(&head, value);
                break;
            case 5:
                delete_end(&head);
                break;
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);
                found = search(head, value);
                if (found != NULL) 
                {
                    printf("Element %d found in the list.\n", value);
                } 
                else 
                {
                    printf("Element %d not found in the list.\n", value);
                }
                break;
            case 7:
                printf("Enter value to count occurrences: ");
                scanf("%d", &value);
                int occurrences = count(head, value);
                printf("Element %d occurs %d times in the list.\n", value, occurrences);
                break;
            case 8:
                printf("Enter value: ");
                scanf("%d", &value);
                printf("Enter position: ");
                scanf("%d", &position);
                insert_at_position(&head, value, position);
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
