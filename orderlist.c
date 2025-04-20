#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	struct node *link;
}NODE;

typedef struct list
{
	NODE *head;
}LIST;
void init_list(LIST *ptr_list);
void insert_order(LIST *ptr_list,int x);
void display(LIST *ptr_list);
int main()
{
	LIST l; // variable for the LIST structure
	init_list(&l);
	int x;
	display(&l);
	while(1)
	{
		printf("\nEnter the element:\n");
		scanf("%d",&x);
		if(x==0)
		{
			break;
		}
		insert_order(&l,x);
		display(&l);
	}
}

void init_list(LIST *ptr_list)
{
	ptr_list->head = NULL;
}

void insert_order(LIST *ptr_list,int x)
{
	//create node
	NODE *temp = (NODE*)malloc(sizeof(NODE));
	temp->data = x;
	temp->link = NULL;
	NODE *prev,*pres;
	prev = NULL;
	pres = ptr_list->head;
	while((pres!=NULL) && (x>pres->data))
	{
		prev = pres;
		pres = pres->link;
	}
	if(pres!=NULL)// position found
	{
		if(prev==NULL) // first postion,inserting a smallest number
		{
			ptr_list->head = temp;
			temp->link = pres;
		}
		else // prev is not NULL, insert somewhere in the middle of the list
		{
			temp->link = pres;
			prev->link = temp;
		}
	}
	else //pres is NULL
	{
		if(prev == NULL)
		{
			ptr_list->head = temp;
		}
		else // inserting the largest element
		{
			prev->link = temp;
		}
	}

}
void display(LIST *ptr_list)
{
	NODE *pres;
	//IS EMPTY
	if(ptr_list->head == NULL)
	{
		printf("Empty LIST\n");
	}
	else
	{
		pres = ptr_list->head;
		while(pres!=NULL)
		{
			printf("%d-->",pres->data);
			pres=pres->link;
		}
	}
}