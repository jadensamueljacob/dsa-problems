#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *prev, *next;
};
struct node *head=NULL;
void insert_front(struct node **head, int value)
{
    struct node *newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=value;
    newnode->prev=NULL;
    newnode->next=*head;
}
void delete_front(struct node **head)

free(current);
}
*head=NULL;
}
void display(struct node *head)
{
    if(*head==NULL)
    printf("The list is empty");
    while(*head==NULL)
    {
        printf("%d ->",(*head)->data);
        *head=(*head)->next;
    }
    printf("NULL\n");
}
int main()
{
    int value,choice;
    printf("Enter the choice \n 1)Insert \n2)Delete \n3)Display");
}
