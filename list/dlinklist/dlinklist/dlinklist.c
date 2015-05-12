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

#include "dlinklist.h"

dlinklist_t CreateEmptyDLinklist()
{
	dlinklist_t list;

	list = (dlinklist_t)malloc(sizeof(dlinknode_t));
	if (NULL != list) {
		list->prev = NULL;
		list->next = NULL;
	}
	return list;
}

void DestroyDLinklist(dlinklist_t list)
{
	if (NULL != list) {
		ClearDLinklist(list);
		free(list);
	}
}

void ClearDLinklist(dlinklist_t list)
{
	dlinklist_t node; /* pointer to the node to be removed */
	
	if (NULL == list) return;

	while (NULL != list->next) {
		node = list->next;
		list->next = node->next;
		free(node);
	}

	return;
}

int LengthDLinklist(dlinklist_t list)
{
	int len = 0;
	dlinknode_t *node;

	if (!list) return -1;
		
	node = list->next;
	while (NULL != node) {
		len++;
		node = node->next;
	}

	return len;
}

int EmptyLinklist(dlinklist_t list)
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

int InsertDLinklist(dlinklist_t list, int at, data_t x)
{
	/* 
	 * node_at and pos_at are used to locate the position of node_at.
	 * node_prev follows the node_at and always points to previous node 
	 *	of node_at.
	 * node_new is used to point to the new node to be inserted.
	 */
	dlinknode_t 	*node_at, *node_prev, *node_new;
	int		pos_at;
	int 		found = 0;

	if (!list) return -1;

	/* at must >= 0 */
	if (at < 0) return -1;

	node_new = malloc(sizeof(dlinknode_t));
	if (NULL == node_new) {
		return -1;
	}
	node_new->data = x; /* assigned value */
	node_new->prev = NULL;
	node_new->next = NULL;

	node_at = list->next;
	node_prev = list;
	pos_at = 0;
	while (NULL != node_at) {
		if (pos_at == at) { 
			found = 1; /* found the position of 'at' */
			break;			
		}

		/* move to the next */
		node_prev = node_at;
		node_at = node_at->next;
		pos_at++;
	}

	if (found) {
		/* insert before list[at] */
		node_new->prev = node_at->prev;
		(node_at->prev)->next = node_new;
		node_new->next = node_at;
		node_at->prev = node_new;
	} else {
		/* 
		 * if not found, means the provided "at"
		 * exceed the range of the list, just 
		 * append the new node to the end of the list
		 * note when we reach the end of the linked-list,
		 * node_at equals to NULL, then we can not use
		 * node_at->prev to locate the previous node 
		 * before note_at, that's why we still have to
		 * maintain a node_prev at the same time for 
		 * this case
		 */
		node_prev->next = node_new;
		node_new->prev = node_prev;
	}
		
	return 0;
}

int DeleteDLinklist(dlinklist_t list, int at)
{
	dlinknode_t 	*node_at;
	int		pos_at;
	int 		found = 0;

	if (!list) return -1;

	/* at must >= 0 */
	if (at < 0) return -1;

	node_at = list->next;
	if (NULL == node_at) {
		/* the list is empty */
		return 0;
	}
	pos_at = 0;
	while (NULL != node_at) {

		if (pos_at == at) { 
			found = 1; /* found the position */
			break;			
		}

		/* move to the next */
		node_at = node_at->next;
		pos_at++;
	}

	if (found) {
		node_at->prev->next = node_at->next;
		/* 
		 * consider the case when the node_at is located
		 * at the end of the list. In this case, 
		 * node_at->next equals to NULL 
		 */
		if (NULL != node_at->next) {
			node_at->next->prev = node_at->prev;
		}

		free(node_at);

		return  0;
	} else {
		return -1;
	}
}
