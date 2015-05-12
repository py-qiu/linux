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
 /*
  * requirements:
  * typedef int data_t;
  * 1) create a empty sequence list
  * 2) init a data_t array, length is 10, insert elements according to
  *	the array.
  * 3) get data_t at the position 4
  * 4) modify value of element at position 4, print it after set
  * 5) delete the element at pos 4
  * 6) get value of element at pos 4 after step 5
  * 7) visit the list and print the value of each element
  * 8) clear the list
  * 9) visit the list after step 8
  */
#include <stdio.h>
#include <stdlib.h>

#include "datatype.h"
#include "seqlist.h"

void iterate_list(seqlist_t *list)
{
	int i;
	
	printf("list.last = %d, list = {", list->last);
	
	for (i = -1; i < list->last;) {
		printf("%d,", list->data[++i]);
	}
		
	if (LengthSqlist(list) > 0)
		printf("\b}\n");
	else
		printf("}\n");
}

int main(int argc, char *argv[])
{
	int i;
	data_t a[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	data_t x;
	
	seqlist_t *list;
	
	list = CreateEmptySqlist();
	
	if (NULL == list) return -1;
		
	for (i = 0; i < 10; i++) {
		if (InsertSqlist(list, i, a[i]) < 0)
			break;
	}
	iterate_list(list);
	
	GetSqlist(list, 4, &x);
	printf("list[4] = %d\n", x);
	printf("updated list[4] to 100\n");
	SetSqlist(list, 4, 100);
	GetSqlist(list, 4, &x);
	printf("now list[4] = %d\n", x);
	iterate_list(list);
		
	printf("removed list[4]\n");
	DeleteSqlist(list, 4);
	GetSqlist(list, 4, &x);
	printf("now list[4] = %d\n", x);
	printf("and total number of list is %d\n", LengthSqlist(list));
	
	iterate_list(list);
	
	ClearSqlist(list);
	printf("after clear, total number of list is %d\n", LengthSqlist(list));

	iterate_list(list);
		
	DestroySqlist(list);
	
	return 0;
}
