//program to implement circular singly linked list
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *link;
};

typedef struct node NODE;

//last : pointer to last node
struct list
{
	NODE *last;
};

typedef struct list CLIST;

void init_list(CLIST *);
void insert_front(CLIST *, int);
void insert_end(CLIST*,int);
void delete_node(CLIST*, int);
void display(CLIST*);

int main()
{
	int ch,data,pos;
	CLIST l;
	init_list(&l);

    while(1)
	{
		display(&l);
		printf("\n1..insert_head");
		printf("\n2..insert_tail");
		printf("\n3..Display");
		printf("\n4.Delete a node");
		printf("\n5..Exit");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:printf("\nEnter the data...");
			             scanf("%d",&data);
						 insert_front(&l,data);
						 break;
			case 2:printf("\nEnter the data...");
			             scanf("%d",&data);
						 insert_end(&l,data);
						 break;			 
			case 3:display(&l);
			             break;
			 
			case 4:printf("\nEnter the data...");
			             scanf("%d",&data);
						 delete_node(&l,data);	
                         break;	
					   
			case 5:exit(0);
		}
	}
}

void init_list(CLIST * ptr_list)
{
	ptr_list->last=NULL;
}

void insert_front(CLIST *ptr_list, int data)
{
	  NODE *temp,*p;
	//create node and populate
	
		temp=(NODE*)malloc(sizeof(NODE));	
        temp->data=data;
		temp->link=temp;
	
	    p =ptr_list->last;  //get the address the last node;
		
		if(p == NULL) //first node
		 ptr_list->last=temp;
		else
		{
			temp->link=p->link; 
			p->link=temp;
		}
}
			
	void insert_end(CLIST *ptr_list, int data)
{
	  NODE *temp,*p;
	  
	//create node and populate
	
		temp=(NODE*)malloc(sizeof(NODE));	
        temp->data=data;
		temp->link=temp;
	
	    p =ptr_list->last;  		
	  
	     if(p==NULL)  // if empty list
			 ptr_list->last=temp; // first node
		 else
		 {
			temp->link=p->link;  // link after the last node
			p->link=temp; 
			ptr_list->last=temp; // make last point to new last node
		}
			 
}		 
			 
	  void display(CLIST* ptr_list)
	  {
		  NODE *pres, *end ,*prev;
		  if(ptr_list->last==NULL)
			  printf("Empty List\n");
		  else
		  {
			  end =ptr_list->last; //copy last nodes address
			  pres=end->link; // point to the first node
			  
			  while(pres!=end)
			  {
				  printf("%d ->",pres->data);
			     pres=pres->link;
			  }
			   printf("%d ",pres->data); // print the last node
		  }
	  }
	  
	 void delete_node(CLIST* ptr_list, int  data)
	 {
		 
		 NODE *end,*pres,*prev;
		 end=ptr_list->last; //copy addres of the last node
		 pres=end->link; //point to the first node
		 prev=end;
		 
		 
		 while((pres->data!=data)&&(pres!=end))
		 {
			 prev=pres;
			 pres=pres->link;
		 }
		 if(pres->data==data)
		 {
			 //if only one node ?
			 if(pres->link==pres)
				 ptr_list->last=NULL;
			 else 
			 {
				 prev->link=pres->link;  // link the previous node to next node
				 if(pres==end)// if deleting last node
				   ptr_list->last=prev; // change last
			 }
            free(pres);
		 }
       else
           printf("data not found..\n");
	 }	   
