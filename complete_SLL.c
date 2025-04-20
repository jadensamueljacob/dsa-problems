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

void init_list(LIST *ptr_list);
void insert_head(LIST *ptr_list, int data);
void display(LIST *ptr_list);
void insert_end(LIST *ptr_list, int data);
void insert_pos(LIST *ptr_list, int data, int pos);
int count_node_recur(NODE *pres);
int count_node(LIST *ptr_list);
void delete_node(LIST *ptr_list, int data);
void delete_pos(LIST *ptr_list, int pos);
void delete_alternate(LIST *ptr_list);
void print_reverse_recur(NODE *pres);
void print_reverse(LIST *ptr_list);

int main()
{
	LIST l;
	init_list(&l);
	int n, ch, pos;
	while (1)
	{
		printf("\n");
		display(&l);
		printf("\n1..Insert at head\n");
		printf("2..Insert at end\n");
		printf("3..display\n");
		printf("4..Insert at a given position\n");
		printf("5..count number of nodes-recursion\n");
		printf("6..Delete node\n");
		printf("7..Delete node at a given position\n");
		printf("8..Delete alternative nodes\n");
		printf("9..Print reverse order\n");
		printf("10.exit\n");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			printf("\nEnter the element to be inserted..");
			scanf("%d", &n);
			insert_head(&l, n);
			break;
		case 2:
			printf("\nEnter the element to be inserted..");
			scanf("%d", &n);
			insert_end(&l, n);
			break;
		case 3:
			display(&l);
			break;
		case 4:
			printf("\nEnter the element and position ..");
			scanf("%d %d", &n, &pos);
			insert_pos(&l, n, pos);
			break;
		case 5:
			printf("Count the no of nodes using recurion");
			int k = count_node(&l);
			printf("\nthe number of nodes = %d\n", k);
			break;
		case 6:
			printf("Enter the element to be deleted\n");
			scanf("%d", &n);
			delete_node(&l, n);
			break;
		case 7:
			printf("\nEnter the position to delete ..");
			scanf("%d", &pos);
			delete_pos(&l, pos);
			break;
		case 8:
			delete_alternate(&l);
			break;
		case 9:
			printf("The nodes in reverse order\n");
			break;
			print_reverse(&l);
		case 10:
			exit(0);
		}
	}
}
void init_list(LIST *ptr_list)
{
	ptr_list->head = NULL;
}
void insert_head(LIST *ptr_list, int data)
{
	NODE *temp;
	temp = (NODE *)malloc(sizeof(NODE));
	temp->data = data;
	temp->link = NULL;

	// is list empty ?
	if (ptr_list->head == NULL)
		ptr_list->head = temp;
	else
	{
		temp->link = ptr_list->head;
		ptr_list->head = temp;
	}
}
void display(LIST *ptr_list)
{
	NODE *pres;
	// is list empty ?
	if (ptr_list->head == NULL)
		printf("\nEmpty list.\n");
	else
	{
		// copy the address of the first node
		pres = ptr_list->head;
		while (pres != NULL)
		{
			printf("%d-->", pres->data);
			pres = pres->link;
		}
	}
}
void insert_end(LIST *ptr_list, int data)
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

void insert_pos(LIST *ptr_list, int data, int pos)
{
	NODE *pres, *temp, *prev;
	int i;
	// create node and populate
	temp = (NODE *)malloc(sizeof(NODE));
	temp->data = data;
	temp->link = NULL;

	i = 1;
	prev = NULL;
	pres = ptr_list->head;
	// go to the desired position
	while ((pres != NULL) && (i < pos))
	{
		i++;
		printf("i=%d\n", i);
		prev = pres;
		pres = pres->link;
	}
	if (pres != NULL) // position is found some where between the first and last
	{
		if (prev == NULL) // inserting in postion 1
		{
			ptr_list->head = temp;
			temp->link = pres;
		}
		else // prev is not NULL, inserting node in the middle
		{
			temp->link = pres;
			prev->link = temp;
		}
	}
	else // pres NULL
	{
		if (i == pos) // insert at the end
			prev->link = temp;
		else
			printf("\nInvalid position..");
	}
}
int count_node(LIST *ptr_list)
{
	int count = 0;
	count = count_node_recur(ptr_list->head);
	return count;
}

int count_node_recur(NODE *pres)
{
	int count = 0;
	if (pres->link == NULL) // only one node
		return 1;
	count = 1 + count_node_recur(pres->link);
	return count;
}

void print_reverse(LIST *ptr_list)
{
	print_reverse_recur(ptr_list->head);
}

void print_reverse_recur(NODE *pres)
{
	if (pres->link != NULL)
	{
		print_reverse_recur(pres->link);
	}
	printf("%d -> ", pres->data);
}

void delete_node(LIST *ptr_list, int data)
{
	NODE *pres, *prev;
	prev = NULL;
	pres = ptr_list->head;

	// move forward until the node is found
	// or you go beyond the list
	while ((pres != NULL) && (pres->data != data))
	{
		prev = pres;
		pres = pres->link;
	}
	if (pres != NULL) // node  found
	{
		// if first node
		if (prev == NULL) // it is the first node
			ptr_list->head = pres->link;
		else
			prev->link = pres->link;
	}
	else
		printf("Node not found..\n");
	free(pres);
}

void delete_pos(LIST *ptr_list, int pos)
{

	NODE *pres, *prev;
	pres = ptr_list->head;
	prev = NULL;

	int i = 1;
	// move forward until the postion is found
	while ((pres != NULL) && (i < pos))
	{
		i++;
		prev = pres;
		pres = pres->link;
	}

	if (pres != NULL) // position found
	{
		// if first position
		if (prev == NULL)
			ptr_list->head = pres->link; // make head point to second node
		else							 // not the first node
			prev->link = pres->link;
		free(pres);
	}
	else
		printf("Invalid Position..\n");
}

void delete_alternate(LIST *ptr_list)
{
	NODE *pres, *prev;
	pres = ptr_list->head;
	prev = NULL;

	while (pres != NULL)
	{
		if (prev == NULL)
			ptr_list->head = pres->link; // first node
		else
			prev->link = pres->link; // second iteration
		// update the pointers
		prev = pres->link;
		if (prev != NULL)
			pres = prev->link;
		else
			pres = NULL;
	}
}
