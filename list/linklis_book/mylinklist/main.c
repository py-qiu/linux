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

void iterate_list(linklist_t list)
{
	linknode_t *node;
	
	if (!list) return;
		
	printf("list = {");
	
	/* start from the first element */
	node = list->next;
	while (NULL != node) {
		printf("%d->", node->data);
		
		/* move to the next */
		node = node->next;
	}
	
	if (LengthLinklist(list) > 0)
		printf("\b\b} \b\n");
	else
		printf("}\n");
}

int main(int argc, char *argv[])
{
	int i;
	data_t a[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	data_t x;
	
	linklist_t list;
	
	list = CreateEmptyLinklist();
	
	if (NULL == list) return -1;

	printf("insert method 1: insert each elment\n");
	for (i = 0; i < 10; i++) {
		if (InsertLinklist(list, i, a[i]) < 0)
			break;
	}
	iterate_list(list);

	GetLinklist(list, 4, &x);
	printf("list[4] = %d\n", x);
	
	printf("updated list[4] to 100\n");
	SetLinklist(list, 4, 100);
	GetLinklist(list, 4, &x);
	printf("now list[4] = %d\n", x);
	iterate_list(list);
		
	printf("removed list[4]\n");
	DeleteLinklist(list, 4);
	GetLinklist(list, 4, &x);
	printf("now list[4] = %d\n", x);
	printf("and total number of list is %d\n", LengthLinklist(list));
	iterate_list(list);

	printf("insert \"1\" at the %dth position of the list\n", 0);
	InsertLinklist(list, 0, 1);
	iterate_list(list);

	printf("reversed the list\n");
	ReverseLinklist(list);
	iterate_list(list);
	
	ClearLinklist(list);
	printf("after clear, total number of list is %d and ", LengthLinklist(list));
	iterate_list(list);
		
	DestroyLinklist(list);
	
	return 0;
}

