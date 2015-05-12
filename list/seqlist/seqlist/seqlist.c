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

#include "seqlist.h"

seqlist_t *CreateEmptySqlist()
{
	seqlist_t *list;

	list = (seqlist_t *)malloc(sizeof(seqlist_t));
	if (list) {
		list->last = -1;
	}

	return list;
}

void DestroySqlist(seqlist_t *list)
{
	if (NULL != list)
		free(list);
}

int FullSqlist(seqlist_t *list)
{
	if (list) {
		if ((MAX - 1) == list->last) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

int EmptySqlist(seqlist_t *list)
{
	if (list) {
		if (-1 == list->last) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

void ClearSqlist(seqlist_t *list)
{
	if (list) {
		list->last = -1;
	}

	return;
}

int LengthSqlist(seqlist_t *list)
{
	if (list) {
		return (list->last + 1);
	} else {
		return -1;
	}
}


int GetSqlist(seqlist_t *list, int at, data_t *x)
{
	if (!list) return -1;
		
	if ((at < 0) || (at > list->last)) return -1;
	
	if (x) {
		*x = list->data[at];
	}
	
	return 0;
}

int SetSqlist(seqlist_t *list, int at, data_t x)
{
	if (!list) return -1;
		
	if ((at < 0) || (at > list->last)) return -1;
		
	list->data[at] = x;
	
	return 0;
}

int InsertSqlist(seqlist_t *list, int at, data_t x)
{
	int i;
	
	if (!list) return -1;

	if (at < 0) {
		/* at must >=0 */
		return -1;
	}
	
	if (FullSqlist(list)) {
		/* memory space is not sufficient */
		return -2;
	} 
	
	/*
	 * If the "at" exceed the upper limit of the list, 
	 * just append the data at the end of the list;
	 * else move the items after the "at" to make
	 * a space for the new item
	 */
	if (at > list->last) {
		at = list->last + 1;
	} 
	else {
		for (i = list->last; i >= at; i--) {
			list->data[i + 1] = list->data[i];
		}
	}
	list->data[at] = x;
	list->last++;

	return 0;
}

int DeleteSqlist(seqlist_t *list, int at)
{
	int i;
	
	if (!list) return -1;

	if ((at < 0) || (at > list->last)) return 1;

	for (i = at; i < list->last; i++)	{
		list->data[i] = list->data[i + 1];
	}
	list->last--;

	return 0;
}

