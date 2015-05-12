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
#ifndef _DLNK_LIST_H_
#define _DLNK_LIST_H_

#include "datatype.h"

/*
 * double linked list. 
 * Similar as single list, we use the same 
 * structure of dnode_t to represent the header node as that 
 * for data node. So, when the list is first created as empty,
 * a struct of dnode_t would be allocated to represent the header
 * of that list, and its field "data" is of no use.
 */
typedef struct dnode_t {
	data_t data;
	struct dnode_t *prev, *next;
} dlinknode_t, *dlinklist_t;

/* 
 * create an empty double list 
 * Input :	void
 * Output :	void
 * Return :	the pointer to the new list, NULL when failed
 * Note: the returned new list contains one node, but this node is 
 * 	only used as the header. the actual first data node 
 *	will be added as the 2nd node in the list. 
 */
dlinklist_t CreateEmptyDLinklist();

/* 
 * destroy a list 
 * Input:	the list to be destroied. 
 * Output:	void
 * Return:	void
 * Note: after destroy, the list is invalid and can not be
 *	used any more.
 */
void DestroyDLinklist(dlinklist_t list);

/*
 * clear the list
 * Input:	the list to be cleared. 
 * Output:	void
 * Return:	void
 * Note: after clear, the list only contains the header node.
 */
void ClearDLinklist(dlinklist_t list);

/*
 * judge if the list is empty
 * Input:	the list to be tested. 
 * Output:	void
 * Return:
 *	1:	list is empty
 *	0:	not 
 *	-1:	error, e.g. the list is invalid
 */
int EmptyDLinklist(dlinklist_t list);

/*
 * get length of the list 
 * Input:	the list to be tested. 
 * Output:	void
 * Return:
 *	>=0:	length of the list
 *	-1:	error, e.g. the list is invalid
 */
int LengthDLinklist(dlinklist_t list);

/* 
 * Insert element at the specified position. If the "at" exceed the 
 * upper limit of the list, append the data at the end of the list. 
 * e.g. insert a new data into a {}.
 * Input:
 *	list:	the list to be operated.
 *	at:	the position at which to insert the new element, 
 *		position index starts from zero
 *	x:	the data value 
 * Output: void
 * Return:
 *	0 : success; 
 *	-1: error 
 */
int InsertDLinklist(dlinklist_t list, int at, data_t x);

/*
 * delete the element at the position specified
 * Input: 
 *	list:	the list to be operated.
 *	at:	the position at where to delete the element, start from zero
 * Output:	void
 * Return:
 *	0:	success;
 *	!0:	not found or error
 */
int DeleteDLinklist(dlinklist_t list, int at);

#endif /* _DLNK_LIST_H_ */
