#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"dlinklist.h"
#include"datatype.h"

dlinklist_t CreateEmptyDLinklist()
{
	dlinklist_t list;
	
	list = (dlinklist_t)malloc(sizeof(dlinknode_t));
	
	if (list)
	{
		list->prev = NULL;
		list->next = NULL;
	}
	
	return list;
}


void ClearDLinklist(dlinklist_t list)
{
	assert(list);
	
	dlinklist_t p;
	
	p = list->next;
	
	while (p)
	{
		list->next = p->next;
		free(p);
		p = list->next; 
	}
	
}


void DestroyDLinklist(dlinklist_t list)
{
	assert(list);
	
	ClearDLinklist(list);
	
	free(list);
}


int EmptyDLinklist(dlinklist_t list)
{
	if (!list)
		return -1; //list invalid
	
	dlinklist_t p;
	p = list->next;
	
	if (!p)
		return 1; //empty
	else
		return 0; //not empty
		
}


int LengthDLinklist(dlinklist_t list)
{
	if (!list)
		return -1; //list invalid
	
	dlinklist_t p;
	p = list->next;
	
	int count = 0;
	
	while (p)
	{
		count++;
		p = p->next;	
	}
	
	return count;
	
}


int InsertDLinklist(dlinklist_t list, int at, data_t x)
{
	if (!list)
		return -1; //list invalid
	
	if (at < 0)
		return -1; //at invalid
		
	int pos = 0;
		
	dlinklist_t p;
	p = list->next;
	
	dlinklist_t pre;
	pre = list;
	
	dlinklist_t new;
	new = CreateEmptyDLinklist();
	if (!new)
		return -1; //error
	
	new->data = x;
	
	while (p)
	{
		if (pos == at)
		{
			new->prev = pre;
			new->next = p;
			
			pre->next = new;
			p->prev = new;
			
			return 0;
		}
		else
		{
			pre = p;
			p = p->next;
			pos++;
		}
	}
	
	pre->next = new;
	new->prev = pre;
	
	return 0;
}


int DeleteDLinklist(dlinklist_t list, int at)
{
	if (!list)
		return -1; //list invalid

	if (at < 0)
		return -1; //at invalid
		
	dlinklist_t node_now;
	node_now = list->next;
	
	int pos = 0;
	
	while(node_now)
	{
		if (pos == at)
		{
			if (NULL == node_now->next)
			{
				node_now->prev->next = NULL;
				
				free(node_now);
				
				return 0; //success		
			} 
			else
			{
				node_now->next->prev = node_now->prev;
				node_now->prev->next = node_now->next;
				
				free(node_now);
				
				return 0; //success
			}
		} //end of if(pos == at)
		else
		{
			node_now = node_now->next;
			pos++;
		}
	} //end of while
	
	return -1; //not found
}
