#include <stdio.h>
#include <stdlib.h>     

// Node definition
typedef struct node 
{  // Node definition
    int data;
    struct node *link;
} NODE;

NODE* create_node(int data) 
{
    NODE *temp=(NODE*)malloc(sizeof(NODE));  // Fixed 'sizeoof' typo
    temp->data=data;
    temp->link=NULL;
    return temp;
}

NODE* concatenate(NODE* list1, NODE* list2) 
{
    if (list1==NULL)
        return list2;
    NODE *temp=list1;
    while (temp->link!=NULL)
    {
        temp=temp->link;
    }
    temp->link=list2;
    return list1;
}

int count_element(NODE* head) // Added head parameter
{  
    int count = 0;
    NODE *current=head;
    while (current!=NULL)
    {
        count++;
        current=current->link;
    }
    return count;
}

void display(NODE* head) 
{
    NODE *current=head;
    while (current!=NULL) // Fixed condition and dereferencing
    {  
        printf("%d -> ", current->data);
        current=current->link;
    }
    printf("NULL\n");
}

int main() {
    NODE* list1=create_node(9);
    list1->link=create_node(8);
    list1->link->link=create_node(5);
    
    NODE* list2=create_node(6);
    list2->link=create_node(2);
    list2->link->link=create_node(3);

    printf("Content of list1: \n");
    display(list1);
    
    printf("Content of list2: \n");
    display(list2);
    
    NODE* result = concatenate(list1, list2);
    printf("The concatenated list is: \n");
    display(result);
    
    int count=count_element(result);
    printf("Number of elements is: %d\n", count);

    return 0;
}