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
#include "datatype.h"
#include "bitree.h"

int main()
{
	bitree_t *root;

	bt_data_t bt_array[] = {0, /* reserved [0] */
		'A', 'B', 'C', 'D','E', 0, 'F', 0, 0, 'G', 'H', 0, 0, 'I'
		};

	root = CreateBitree(
		1, 
		bt_array, 
		sizeof(bt_array)/sizeof(bt_data_t) - 1);
	
	printf("PreOrder  : ");
	PreOrder(root);
	printf("\n");

	printf("InOrder   : ");
	InOrder(root);
	printf("\n");

	printf("PostOrder : ");
	PostOrder(root);
	printf("\n");

	printf("NoOrder   : ");
	NoOrder(root);
	printf("\n");

	return 0;
}
