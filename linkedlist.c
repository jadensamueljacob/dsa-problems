#include <stdio.h>
#include <stdlib.h>     

// Node definition
typedef struct node  // node definition or definition of structure and typedef is used to give an alias
{
    int data;
    struct node *link;
} NODE;

NODE *create_node(int value)
{
    NODE *temp = (NODE *)malloc(sizeof(NODE));  // Corrected: temp should be a pointer, and malloc returns a pointer
    if(temp == NULL)  // Check if malloc succeeded
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    temp->data = value;
    temp->link = NULL;
    return temp;
}

void insert_front(int value, NODE **start)
{
    NODE *temp = create_node(value);
    if(*start == NULL)
        *start = temp;
    else
    {
        temp->link = *start;
        *start = temp;
    }
}

void insert_end(int value, NODE **start)
{
    NODE *temp = create_node(value);
    if(*start == NULL)
    {
        *start = temp;
    }
    else
    {
        NODE *current = *start;
        while(current->link != NULL)
        {
            current = current->link;
        }
        current->link = temp;
    }
}

void delete_front(NODE **start)
{
    if(*start == NULL)
    {
        printf("The list is empty\n");
        return;
    }
    NODE *temp = *start;
    *start = (*start)->link;
    printf("The deleted element is: %d\n", temp->data);
    free(temp);
}

void delete_end(NODE **start)
{
    if(*start == NULL)
    {
        printf("The list is empty\n");
        return;
    }
    if((*start)->link == NULL)
    {
        printf("The deleted element is: %d\n", (*start)->data);
        free(*start);
        *start = NULL;
        return;
    }
    NODE *current = *start;
    while(current->link->link != NULL)
    {
        current = current->link;
    }
    printf("The deleted element is: %d\n", current->link->data);
    free(current->link);
    current->link = NULL;
}

void display(NODE *start)
{
    if(start == NULL)
    {
        printf("The list is empty\n");
        return;
    }
    printf("The elements in the list are: ");
    while(start != NULL)
    {
        printf("\t%d", start->data);
        start = start->link;
    }
    printf("\n");
}

int search(int value, NODE *start)
{
    int position = 1;
    while(start != NULL)
    {
        if(start->data == value)
            return position;
        start = start->link;
        position++;
    }
    return -1;  // Not found
}

int main()
{
    int choice, value;
    NODE *start = NULL;
    
    while(1)
    {
        printf("\nEnter the choice: \n1) Insert front \n2) Delete front \n3) Display \n4) Insert end \n5) Delete end \n6) Search \n7) Exit\n");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1: 
                printf("Enter value: ");
                scanf("%d", &value);
                insert_front(value, &start);
                break;
                
            case 2: 
                delete_front(&start);
                break;
                
            case 3: 
                display(start);
                break;
                
            case 4: 
                printf("Enter value: ");
                scanf("%d", &value);
                insert_end(value, &start);
                break;
                
            case 5: 
                delete_end(&start);
                break;

            case 6: 
                printf("Enter value to search: ");
                scanf("%d", &value);
                int position = search(value, start);
                if(position != -1)
                    printf("Element %d found at position %d\n", value, position);
                else
                    printf("Element %d not found in the list\n", value);
                break;

            case 7: 
                printf("Exiting...\n");
                // Free remaining nodes before exiting
                while(start != NULL)
                {
                    delete_front(&start);
                }
                exit(0);
                
            default: 
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}
