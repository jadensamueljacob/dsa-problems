/*stack: ADT - Abstract data type
                - only the features / operations
                - not the implementation
Operations:
1.push(x)
    1. Increment the top = top +1
    2. insert the element to the top
2.pop()
    1. decrement the top = top -1
3. Isempty() - check if the stack is empty or not
The push and pop operations will be performed at one end - top
As stack follows LIFO - Last In First Out

If the top reaches the max size and still a push() has to be performed,
then its -> STACK OVERFLOW

If the top is -1, then its STACK UNDERFLOW - STACK IS EMPTY

Applications:
1. Function calls/Recursion
2. Undo operations on a text editor
3. Compiler uses stack for paranthesis matching to throw errors
*/
// Implementation of a stack using arrays
#include <stdio.h>
#include <stdlib.h>
int push(int *s, int *top, int size, int ele);
int pop(int *s,int *top,int size);
void display(int *s,int top,int size);
int main()
{
    int size, ele, ch,res;
    int top = -1;
    printf("Enter the size of the stack_array:\n");
    scanf("%d", &size);
    int *s = (int *)malloc(sizeof(int) * size);
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
            scanf("%d", &ele);
            res = push(s, &top, size, ele);
            if(res>0)
            {
                printf("Element pushed successfully\n");
            }
            break;
        case 2: res = pop(s,&top,size);
                if(res>0)
            {
                printf("Element popped successfully\n");
            }
            break;
        case 3: display(s,top,size); break;
        //no changes to the top; call by value
        case 4:
            exit(0);
        }
    }
}
int push(int *s, int *top, int size, int ele)
{
    if (*top == size - 1)
    {
        printf("STACK IUS OVERFLOWING");
        return 0;
    }
    *top = *top + 1; //(*top)++ // ++*top
    s[*top] = ele;
    return 1;
}
int pop(int *s,int *top,int size)
{
    if(*top == -1)
    {
        printf("Stack is underflow\n");
        return 0;
    }
    int ele = s[*top]; // element at the top that is deleted
    *top = *top - 1; //--*top //(*top)--
    return ele;
}
void display(int *s,int top,int size)
{
    int i;
    if(top == -1)
    {
        printf("Stack empty:\n");
    }
    else
    {
        for(i=top;i>=0;i--)
        {
            printf("%d ",s[i]);
        }
    }
}
