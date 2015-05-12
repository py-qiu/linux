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
#ifndef _LNK_LIST_H_
#define _LNK_LIST_H_

#include "datatype.h"

/*
 * There are many methods to implement a linked list. 
 * The method we choose here is the most simple one - a single
 * linked list.
 * Despite of many solutions, generally there is a list header
 * defined to represent the list object. Here we use the same 
 * structure of node_t to represent the header node as that 
 * for data node. So, when the list is first created as empty,
 * a struct of node_t would be allocated to represent the header
 * of that list, and its field "data" is of no use while the 
 * field "next" is set to NULL. Details please refer to the
 * definition of function - CreateEmptyLinklist. 
 */
typedef struct node_t {
	data_t data;
	struct node_t *next;
} linknode_t, *linklist_t;

/* 
 * create an empty list 
 * Input :	void
 * Output :	void
 * Return :	the pointer to the new list, NULL when failed
 * Note: the returned new list contains one node, but this node is 
 * 	only used as the header. the actual first data node 
 *	will be added as the 2nd node in the list. 
 */
linklist_t CreateEmptyLinklist();

/* 
 * destroy a list 
 * Input:	the list to be destroied. 
 * Output:	void
 * Return:	void
 * Note: after destroy, the list is invalid and can not be
 *	used any more.
 */
void DestroyLinklist(linklist_t list);

/*
 * clear the list
 * Input:	the list to be cleared. 
 * Output:	void
 * Return:	void
 * Note: after clear, the list only contains the header node.
 */
void ClearLinklist(linklist_t list);

/*
 * judge if the list is empty
 * Input:	the list to be tested. 
 * Output:	void
 * Return:
 *	1:	list is empty
 *	0:	not 
 *	-1:	error, e.g. the list is invalid
 */
int EmptyLinklist(linklist_t list);

/*
 * get length of the list 
 * Input:	the list to be tested. 
 * Output:	void
 * Return:
 *	>=0:	length of the list
 *	-1:	error, e.g. the list is invalid
 */
int LengthLinklist(linklist_t list);

/*
 * get data of element at specified position
 * Input : 
 *	list:	the list to be operated.
 *	at:	the position where to get the element at, 
 *		pos starts from zero
 * Output:
 *	x:	the data value got and returned
 * Return:
 *	0:	success;
 *	-1:	error, e.g. the element is not found
 */
int GetLinklist(linklist_t list, int at, data_t *x);

/*
 * set/update data of element at specified position
 * Input : 
 *	list:	the list to be operated.
 *	at:	the position at where to set the element, 
 *		pos starts from zero
 *	x:	the new data value
 * Output:	void
 * Return:
 *	0:	success;
 *	-1:	error
 */
int SetLinklist(linklist_t list, int at, data_t x);

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
int InsertLinklist(linklist_t list, int at, data_t x);

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
int DeleteLinklist(linklist_t list, int at);

/*
 * reverse the list
 * Input : 
 *	list: the list to be operated.
 * Output: void
 * Return: the reversed list
*/
linklist_t ReverseLinklist(linklist_t list);

linklist_t MergeLinklist(linklist_t list_a, linklist_t list_b);
#endif /* _LNK_LIST_H_ */
