#include <stdio.h>
#include <stdlib.h>
#define MAX 5

void enqueue(int q[], int *rear, int *front, int ele)
{
    int pos;
    if (*rear == MAX - 1)
    {
        printf("Overflow condition\n");
    }
    else
    {
        pos = *rear;
        (*rear)++;
        while (pos >= 0 && q[pos] >= ele)
        {
            q[pos + 1] = q[pos];
            pos--;
        }
        q[pos + 1] = ele;
        if (*front == -1)
        {
            *front = 0; //*front = *front + 1
        }
    }
}

void display(int q[], int r, int f)
{
    if (f == -1 || f > r)
    {
        printf("Underflow condition\n");
    }
    else
    {
        for (int i = f; i <= r; i++)
        {
            printf("%d\t", q[i]);
        }
        printf("\n");
    }
}

int dequeue(int q[], int *f, int *r)
{
    int x;
    if (*f == -1 || *f > *r)
    {
        return 9999;
    }
    else
    {
        x = q[*f];
        (*f)++;
        if (*f > *r) // Reset the queue when all elements are dequeued
        {
            *f = -1;
            *r = -1;
        }
        return x;
    }
}

int main()
{
    int q[MAX], front = -1, rear = -1;
    int ele, ch, x;
    while (1)
    {
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter the choice:\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the element:\n");
            scanf("%d", &ele);
            enqueue(q, &rear, &front, ele);
            break;
        case 2:
            x = dequeue(q, &front, &rear);
            if (x == 9999)
                printf("Underflow condition\n");
            else
                printf("Deleted element is %d\n", x);
            break;
        case 3:
            display(q, rear, front);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
