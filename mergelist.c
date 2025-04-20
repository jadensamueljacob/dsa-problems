#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *link;
};

typedef struct node NODE;

struct list
{
	NODE *head;
};

typedef struct list LIST;

void init_list(LIST *);
void insert_order(LIST *, int);
void display(LIST *);
void create_list(LIST *);
void merge(LIST *, LIST *, LIST *);
void insert_tail(LIST *, int);

int main()
{
	LIST l1, l2, l3;
	init_list(&l1);
	init_list(&l2);
	init_list(&l3);

	printf("\nCreating List one..\n");
	create_list(&l1);
	printf("displaying List one..\n");
	display(&l1);
	printf("\nCreating List Two..\n");
	create_list(&l2);
	printf("displaying List Two..\n");
	display(&l2);
	printf("\nMerging both the Lists..\n");
	merge(&l1, &l2, &l3);
	printf("\ndisplaying merged list..\n");
	display(&l3);
}

void init_list(LIST *ptr_list)
{
	ptr_list->head = NULL;
}

void create_list(LIST *ptr_list)
{
	int x;
	while (1)
	{
		printf("\nEnter the Element..");
		scanf("%d", &x);
		if (x == 0)
			break;
		insert_order(ptr_list, x);
	}
}

void insert_order(LIST *ptr_list, int data)
{
	NODE *pres, *prev, *temp;
	prev = NULL;
	pres = ptr_list->head;

	temp = (NODE *)malloc(sizeof(NODE));
	temp->data = data;
	temp->link = NULL;

	while ((pres != NULL) && (data > pres->data))
	{
		prev = pres;
		pres = pres->link;
	}
	if (pres != NULL) // position found
	{
		if (prev == NULL) // insert smallest no (in front)
		{
			temp->link = pres;
			ptr_list->head = temp;
		}
		else // between 2 and last but one node
		{
			temp->link = pres;
			prev->link = temp;
		}
	}
	else // pres=NULL
	{
		if (prev == NULL)		   // empty list
			ptr_list->head = temp; // first element
		else
			prev->link = temp; // insert at end(max number)
	}
}

void display(LIST *ptr_list)
{
	NODE *pres;
	if (ptr_list->head == NULL) // empty list
		printf("Empty List..\n");
	else
	{
		pres = ptr_list->head;
		while (pres != NULL) // list present
		{
			printf("%d-> ", pres->data);
			pres = pres->link;
		}
	}
}

void merge(LIST *ptr_list1, LIST *ptr_list2, LIST *ptr_list3)
{
	NODE *p, *q;

	p = ptr_list1->head;
	q = ptr_list2->head;

	// traverse the lists until you reach the end of one of the lists
	while ((p != NULL) && (q != NULL))
	{
		if (p->data < q->data)
		{
			insert_tail(ptr_list3, p->data);
			p = p->link;
		}
		else
		{
			insert_tail(ptr_list3, q->data);
			q = q->link;
		}
	}
	if (p == NULL) // first list has come to end
	{
		while (q != NULL) // insert the nos of the second list
		{
			insert_tail(ptr_list3, q->data);
			q = q->link;
		}
	}
	else
	{
		while (p != NULL)
		{
			insert_tail(ptr_list3, p->data);
			p = p->link;
		}
	}
}

void insert_tail(LIST *ptr_list, int data)
{
	NODE *pres, *temp;
	// create node and populate
	temp = (NODE *)malloc(sizeof(NODE));
	temp->data = data;
	temp->link = NULL;

	// is the list empty?

	if (ptr_list->head == NULL)
		ptr_list->head = temp;
	else
	{
		// list not empty, go to end of list
		pres = ptr_list->head; // copy address of the first node
		while (pres->link != NULL)
		pres = pres->link;
		pres->link = temp;
	}
}
