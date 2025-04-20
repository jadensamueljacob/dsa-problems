#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
struct node *top=NULL;
int choice, x;

void push()
{
    struct node *newnode=(struct node*)malloc(sizeof(struct node));
    if(newnode==NULL)
    {
        printf("Memory is not being allocated hence we can't insert an element");
    }
    else
    {
        printf("Enter the element to be inserted\n");
        scanf("%d",&x);
        newnode->data=x;
        newnode->next=top;
        top=newnode;
    }

}

void pop()
{
    if(top==NULL)
    {
        printf("Stack is underflow");
    }
    else
    {
        struct node *temp=top;
        printf("The element to be deleted is %d\n",temp->data);
        top=top->next;
        free(temp);
    }
}

void peek()
{
    if(top==NULL)
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("The top element is %d\n",top->data);
    }
}

void display()
{
    if (top==NULL)
    {
        printf("Stack is empty\n");
    }
    else
    {
        struct node *temp=top;
        printf("The element in stack are\n");
        while(temp!=NULL)
        {
            printf("%d ",temp->data);
            temp=temp->next;
        }
    }
}

int main()
{
    printf("Enter the stack operation \n1) Push() \n2) Pop() \n3) Peek() \n4) Display() \n5)Exit");
    do
    {
        printf("\nEnter the choice \n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: push();
                    break;
            case 2: pop();
                    break;
            case 3: peek();
                    break;
            case 4: display();
                    break;
            default: printf("Invalid choice");
                    exit(1);
        }
    }while(choice!=5);
    return 0;
}