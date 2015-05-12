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

void iterate_list(dlinklist_t list)
{
	dlinknode_t *node;
	
	if (!list) return;
	
	printf("list = {");
	
	/* start from the first element */
	node = list->next;
	while (NULL != node) {

		printf("<-%d->", node->data);
		
		/* move to the next */
		node = node->next;
	}
	
	printf("}\n");
}

int main(int argc, char *argv[])
{
	int i;
	data_t a[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	
	dlinklist_t list;
	
	list = CreateEmptyDLinklist();
	
	if (NULL == list) return -1;

	printf("insert each elment\n");
	for (i = 0; i < 10; i++) {
		if (InsertDLinklist(list, i, a[i]) < 0)
			break;
	}
	iterate_list(list);

	printf("removed list[4]\n");
	DeleteDLinklist(list, 4);
	iterate_list(list);

	printf("insert \"1\" at the %dth position of the list\n", 0);
	InsertDLinklist(list, 0, 1);
	iterate_list(list);

	ClearDLinklist(list);
	printf("after clear, total number of list is %d and ", LengthDLinklist(list));
	iterate_list(list);
		
	DestroyDLinklist(list);
	
	return 0;
}

