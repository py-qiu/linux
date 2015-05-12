#include<stdio.h>
#include"linklist.h"
#include<stdlib.h>
#include<assert.h>

linklist_t CreateEmptyLinklist()
{
	linklist_t p = NULL;
	
	p = (linklist_t)malloc(sizeof(linknode_t));
	
	if (p)
	{
		p->next = NULL;
	}
		
	return p;
}


void ClearLinklist(linklist_t list)
{
	assert(list);
	
	linklist_t temp = NULL;
	
	temp = list->next;
	
	while (temp)
	{
		list->next = temp->next;
		free (temp);
		temp = list->next;
	}
}


void DestroyLinklist(linklist_t list)
{
	assert(list);
	
	ClearLinklist(list);
	
	free(list);
}

int EmptyLinklist(linklist_t list)
{
	if (!list)
		return -1; //error,list invalid
		
	if (list->next) //if next != NULL
		return 0;  //not empty
	else
		return 1;  //empty
}

int LengthLinklist(linklist_t list)
{
	if (!list)
		return -1; //list invalid
	
	int count = 0;
	
	linklist_t p;
	p = list->next;
	
	while (p)
	{
		count++;
		p = p->next;
	}
	
	return count;
}

int GetLinklist(linklist_t list, int at, data_t *x)
{
	linklist_t p = list->next;
	int j = 0;

	while ((j++ < at) && (p = p->next));

	if ((!p) || (j <= at))
	{
		return -1;
	}

	*x = p->data;
	return 0;
/*
	assert(list);
	assert(x);
	assert(at > 0);
	
	int position = 0;
	linklist_t p;
	p = list->next;
	
	while (p) //next != NULL
	{
		if (at == position)
		{
			*x = p->data;
			return 0; //success
		}
		
		p = p->next;
		position++;
	}
	
	return -1; //error,not found, or empty
*/
}


int SetLinklist(linklist_t list, int at, data_t x)
{
	assert(list);
	assert(at > 0);
	
	int position = 0;
	
	linklist_t p;
	p = list->next;
	
	while(p)
	{
		if (at == position)
			{
				p->data = x;
				
				return 0; //success
			}
			
			position++;
			p = p->next;
	}
	
	return -1; //error, empty, or not found
}


int InsertLinklist(linklist_t list, int at, data_t x)
{
	if (!list)
		return -1; //error,list invalid
	
	linklist_t prev = list;
	linklist_t new;
	new = (linknode_t *)malloc(sizeof(linknode_t));
	assert(new);
	new->data = x;
	new->next = NULL;

	linklist_t p = list->next;
	
	int position = 0;
	
	
	while (p)
	{
		if (at == position)
		{
			new->next = p;
			prev->next = new;
			
			return 0; //success
		}
		else
		{
			prev = p;
			p = p->next;
			position++;
		}
	}
	
	prev->next = new;
	return 0;
}


int DeleteLinklist(linklist_t list, int at)
{
	if (!list)
		return -1; //error, list invalid
		
	assert(at > 0);
	
	int position = 0;
	
	linklist_t prev = list;
	linklist_t p = list->next;
	
	while(p)
	{
		if (position == at)
		{
			prev->next = p->next;
			free(p);
			
			return 0; //success
		}
		else
		{
			prev = p;
			p = p->next;
			position++;
		}
	}
	
	return -1; //error, not found
}


#if 0
linklist_t ReverseLinklist(linklist_t list)
{
	assert(list);

	linklist_t node, node2;
	node = list->next;

	list->next = NULL;

	while (node) //用node遍历链表
	{
		node2 = node;
		node = node->next;

		node2->next = list->next; //list不断回退
		list->next = node2;
	}

	return list;
}
#endif


#if 1
linklist_t ReverseLinklist(linklist_t list)
{
	assert(list);

	linklist_t prev, now, next;

	prev = NULL;
	now = list->next;
	list->next = NULL;

	while (now)
	{
		next = now->next;

		if (next == NULL)
		{
			list->next = now;
		}
		
		now->next = prev;
		prev = now;
		now = next;
	}

	return list;
}
#endif
