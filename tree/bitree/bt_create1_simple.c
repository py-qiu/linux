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
 * this file is a simplified version of bt_create1.c
 * removed all printf trace statements.
 */
#include <stdlib.h>
#include <stdio.h>

typedef char bt_data_t;

typedef struct tree_node_t
{
	bt_data_t data;
	struct tree_node_t *lchild, *rchild;
}bitree_t;

bitree_t *CreateBitree(int i, bt_data_t a[], int n);

int main()
{
	bt_data_t bt_array[] = {0, /* reserved [0] */
		'a', 'b', 'c', 'd','e', 'f', 'g', 'h', 'i', 'j'
		};
		
	bitree_t *root;

	printf("Begin creating B-tree ...\n");
	
	root = CreateBitree(1, bt_array, sizeof(bt_array)/sizeof(bt_data_t) - 1 );
	
	printf("Finished!\n");
	
	return 0;
}

/* 
 * i: index of root node
 * a: array stores the B-tree
 * n: total number of nodes 
 */
bitree_t *CreateBitree(int i, bt_data_t a[], int n)
{
	bitree_t *root;
	int j;
	
	root = (bitree_t *)malloc(sizeof(bitree_t));
	root->data = a[i];
	
	j = 2 * i;	
	if (j <= n) {
		/* must have left child */
		root->lchild = CreateBitree(j, a, n);
	} else {
		root->lchild = NULL;
	}
	
	j = 2 * i + 1;
	if (j <= n) {
		/* must have right child */
		root->rchild = CreateBitree(j, a, n);
	} else {
		root->rchild = NULL;
	}

	return root;
}
