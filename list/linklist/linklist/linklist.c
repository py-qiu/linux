/*
 * (C) Copyright 2014
 * http://www.farsight.com.cn/
 * http://nj.hqyj.com/
 * 
 * This program is distributed in the purpose for training only
 * and hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Revision history
 * ------------------------------------------------------
 * 20140928	unicornx	initial archived
 */
#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"

linklist_t CreateEmptyLinklist()
{
	linklist_t list;

	list = (linklist_t)malloc(sizeof(linknode_t));
	if (NULL != list) {
		list->next = NULL;
	}
	return list;
}

void DestroyLinklist(linklist_t list)
{
	if (NULL != list) {
		ClearLinklist(list);
		free(list);
	}
}

void ClearLinklist(linklist_t list)
{
	linklist_t node; /* pointer to the node to be removed */
	
	if (NULL == list) return;

	while (NULL != list->next) {
		node = list->next;
		list->next = node->next;
		free(node);
	}

	return;
}

int LengthLinklist(linklist_t list)
{
	int len = 0;
	linknode_t *node;

	if (!list) return -1;
		
	node = list->next;
	while (NULL != node) {
		len++;
		node = node->next;
	}

	return len;
}

int EmptyLinklist(linklist_t list)
{
	if (NULL != list) {
		if (NULL == list->next) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

int GetLinklist(linklist_t list, int at, data_t *x)
{
	linknode_t *node;	/* used for iteration */
	int pos;		/* used for iteration and compare with */

	if (!list) return -1;

	/* at must >= 0 */
	if (at < 0) return -1;

	/* start from the first element */
	node = list->next;
	pos = 0;
	while (NULL != node) {

		if (at == pos) {
			if (x) {
				*x = node->data;
			}
			return 0;			
		}
		
		/* move to the next */
		node = node->next;
		pos++;
	}

	return -1;
}

int SetLinklist(linklist_t list, int at, data_t x)
{
	linknode_t *node; /* used for iteration */
	int pos;
	int found;

	if (!list) return -1;
		
	node = list->next;
	pos = -1;
	found = 0;
	while (NULL != node) {
		pos++;
		if (at == pos) { 
			found = 1; /* found the position */
			node->data = x;
			break;			
		}
		node = node->next;
	}

	if (found) {
		return 0;
		
	} else {
		return -1;
	}
}

int InsertLinklist(linklist_t list, int at, data_t x)
{
	/* 
	 * node_at and pos_at are used to locate the position of node_at.
	 * node_prev follows the node_at and always points to previous node 
	 *	of node_at.
	 * node_new is used to point to the new node to be inserted.
	 */
	linknode_t 	*node_prev, *node_at, *node_new;
	int		pos_at;
	int 		found = 0;

	if (!list) return -1;

	/* at must >= 0 */
	if (at < 0) return -1;

	node_new = malloc(sizeof(linknode_t));
	if (NULL == node_new) {
		return -1;
	}
	node_new->data = x; /* assigned value */
	node_new->next = NULL;

	node_prev = list;
	node_at = list->next;
	pos_at = 0; 
	while (NULL != node_at) {
		if (pos_at == at) {
			/* 
			 * found the node 'at'
			 */ 
			found = 1;
			break;			
		}

		/* move to the next pos_at */
		node_prev = node_at;
		node_at = node_at->next;
		pos_at++;
	}
	
	if (found) {
		/* insert */
		node_new->next = node_prev->next;
		node_prev->next = node_new;
	} else {
		/* 
		 * If not found, means the provided "at"
		 * exceeds the upper limit of the list, just 
		 * append the new node to the end of the list.
		 */
		node_prev->next = node_new;
	}
	
	return 0;
}

int DeleteLinklist(linklist_t list, int at)
{
	/* 
	 * node_at and pos_at are used to locate the position of node_at.
	 * node_prev follows the node_at and always points to previous node 
	 *	of node_at.
	 */
	linknode_t 	*node_prev, *node_at;
	int		pos_at;
	int 		found = 0;

	if (!list) return -1;

	/* at must >= 0 */
	if (at < 0) return -1;

	node_prev = list;
	node_at = list->next;
	pos_at = 0; 
	while (NULL != node_at) {
		if (pos_at == at) {
			/* 
			 * found the node 'at'
			 */ 
			found = 1;
			break;			
		}

		/* move to the next pos_at */
		node_prev = node_at;
		node_at = node_at->next;
		pos_at++;
	}
	
	if (found) {
		/* remove */
		node_prev->next = node_at->next;
		free(node_at);

		return  0;
	} else {
		return -1;
	}
}

/*
 * Method 1:
 * Create a new list (initialized as empty).
 * From the original list, start from the first node, take it out and
 * insert it into the front of the new list.
 * Return the new list as the reversed list. 
 */
linklist_t ReverseLinklist(linklist_t list)
{
	linknode_t *node, *node2;

	if (!list) return NULL;
	
	/* set node pointer to the first element of the list */
	node = list->next;

	/* reset list header to NULL */
	list->next = NULL;
	
	while (NULL != node) {
		/* backup node to node2 */
		node2 = node;
		/* move node to the next */
		node = node->next;

		/* insert the node2 into the list and put
		 * it at the first position of the list 
		 */
		node2->next = list->next;
		list->next = node2;
	}
	
	return list;
}

#if 0
/* 
 * Method 2:
 * Operate on the existing list, not create another new one.
 * From the head of the list, switch the direction (->next)
 * between the adjacent two elements. e.g.
 * original:	1->2->3->4->null
 * step1: null<-1  2->3->4->null
 * step2: null<-1<-2  3->4->null
 * step3: null<-1<-2<-3  4->null
 * step4: null<-1<-2<-3<-4
 */
linklist_t ReverseLinklist(linklist_t list)
{
	linknode_t *node_prev, *node, *node_next;

	if (!list) return NULL;
	
	node_prev = NULL;
	node = list->next;
	while (NULL != node) {
		node_next = node->next;
	
		/* if the next node is null, the current node
		 * reaches the end of original list, 
		 * make the list head point to the current node
		 */
		if (NULL == node_next) {
			list->next = node;
		}
		
		/* reverse the linkage between nodes */		
		node->next = node_prev;
		
		/* move forward */
		node_prev = node;
		node = node_next;
	}
	
	return list;
}
#endif



