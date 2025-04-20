#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int data;
	int prior;
	struct node *link;
} NODE;

void enqueue(NODE *ptr, int ele, int p)
{
	NODE *temp = malloc(sizeof(NODE));
	temp->data = ele;
	temp->prior = p;
	temp->link = NULL;
	if (ptr->link == NULL)
	{
		ptr->link = temp;
		return;
	}
	if (p < ptr->link->prior)
	{
		temp->link = ptr->link;
		ptr->link = temp;
		return;
	}
	NODE *cur = ptr->link;
	NODE *prev = NULL;
	while (cur != NULL && p > cur->prior)
	{
		prev = cur;
		cur = cur->link;
	}
	prev->link = temp;
	temp->link = cur;
}
void display(NODE *ptr)
{
	if (ptr->link == NULL)
	{
		printf("empty\n");
	}
	else
	{

		NODE *cur = ptr->link;
		while (cur != NULL)
		{
			printf("%d\t", cur->data);
			cur = cur->link;
		}
	}
}
int main()
{
	NODE *front = malloc(sizeof(NODE));
	front->link = NULL;
	int ch, ele, pri, x;
	while (1)
	{
		printf("1.enqueue\n 2.dequeue\n 3.display\n");
		printf("enter your choice\n");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			printf("enter the element and priority\n");
			scanf("%d%d", &ele, &pri);
			enqueue(front, ele, pri);
			break;
		case 3:
			display(front);
			break;
		}
	}
}