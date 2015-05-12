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
#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_

#include "datatype.h"

#define MAX 100

typedef struct {
	data_t	data[MAX];
	int	last; /* pointer to the last element of the array */
} seqlist_t;

/* 
 * create a list and init it as empty 
 * Input : void
 * Output: void
 * Return: new list, NULL when failed 
 */
seqlist_t *CreateEmptySqlist();

/* 
 * destroy a list 
 * Input : the list to be destroied. 
 * Output: void
 * Return: void
 */
void DestroySqlist(seqlist_t *list);

/*
 * clear the list and reset it as empty
 * Input : the list to be cleared. 
 * Output: void
 * Return: void
 */
void ClearSqlist(seqlist_t *list);

/* 
 * judge if the list is empty
 * Input:	the list to be tested. 
 * Output:	void
 * Return:
 *	1:	list is empty
 *	0:	not 
 *	-1:	error, e.g. the list is invalid
 */
int EmptySqlist(seqlist_t *list);

/* 
 * judge if the list is full 
 * Input : the list to be tested. 
 * Output: void
 * Return:
 *	1 : list is full
 *	0 : not 
 *	-1: error
 */
int FullSqlist(seqlist_t *list);

/* 
 * get length of the list 
 * Input : the list to be tested. 
 * Output: void
 * Return: 
 * 	>= 0: length of the list;
 *	 -1 : means error 
 */
int LengthSqlist(seqlist_t *list);

/* 
 * Insert element at the specified position. If the "at" exceed the 
 * upper limit of the list, append the data at the end of the list. 
 * e.g. insert a new data into a {}.
 * Input : 
 *	list :	the list to be operated.
 *	at :	the position at which to insert the new element, 
 * 		position index starts from zero.
 *	x :	the data to be inserted 
 * Output: void
 * Return:
 *	0 : success; 
 *	<0: error 
 */
int InsertSqlist(seqlist_t *list, int at, data_t x);

/*
 * delete the element by the position
 * Input : 
 *	list :	the list to be operated.
 *	at :	the position at which to delete the element, 
 *		position index starts from zero
 * Output :	void
 * Return :
 *	0 :	success;
 *	1 :	not found
 *	-1:	error  
 */
int DeleteSqlist(seqlist_t *list, int at);

/*
 * get data of element at specified position
 * Input : 
 *	list :	the list to be operated.
 *	at :	the position where to get the element at, 
 *		position index starts from zero.
 * Output:
 *	x :	the data value returned
 * Return:
 *	0 :	success;
 *	-1:	error, e.g. list is invalid; 'at' extends 
 *		the range of the list    
 */
int GetSqlist(seqlist_t *list, int at, data_t *x);

/*
 * set/update data of element at specified position
 * Input : 
 *	list :	the list to be operated.
 *	at :	the position at where to set the element, 
 *		position index starts from zero
 *	x :	the new data value
 * Output: void
 * Return:
 *	0 :	success;
 *	-1:	error, e.g. list is invalid; 'at' extends the 
 *		range of the list   
 */
int SetSqlist(seqlist_t *list, int at, data_t x);

#endif /* _SEQ_LIST_H_ */