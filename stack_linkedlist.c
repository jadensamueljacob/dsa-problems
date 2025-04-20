#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *link;
}NODE;
typedef struct stack
{
    NODE *top;
}STACK;
void display(STACK *ptr);
void init(STACK *ptr);
void push(STACK *ptr,int ele);
int pop(STACK *ptr);

int main()
{
    STACK st;
    int ele,ch,res;
    init(&st);
     while (1)
    {
        printf("\n1.push\n");
        printf("2.pop\n");
        printf("3.display\n");
        printf("Enter the option:\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the element:\n");
            scanf("%d",&ele);
            push(&st,ele);
            break;
        case 2: 
            res = pop(&st);
            if(res>0)
            {
                printf("The element that is popped is:%d\n",res);
            }
            break;
        case 3: display(&st); break;
        //no changes to the top; call by value
        case 4:
            exit(0);
        }
    }
}
void init(STACK *ptr)
{
    ptr->top = NULL;
}
void push(STACK *ptr,int ele)
{
    // create and populate the node
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    temp->data = ele;
    temp->link = NULL;

    temp->link = ptr->top;
    ptr->top = temp;
}
int pop(STACK *ptr)
{
    NODE *p;
    int data;
    p = ptr->top;
    if(p == NULL)
    {
        printf("Empty stack\n");
        return 0;
    }
    data = p->data;
    ptr->top = p->link;
    free(p);
    return(data);
}
void display(STACK *ptr)
{
    NODE *p = ptr->top;
    if(p == NULL)
    {
        printf("EMpty stack");
    }
    else
    {
        //traverse the list
        while(p!=NULL)
        {
            printf("%d-->",p->data);
            p = p->link;
        }
    }
}
