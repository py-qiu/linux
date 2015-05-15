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
#include <stdlib.h>
#include <stdio.h>

typedef char bt_data_t;

typedef struct tree_node_t
{
	bt_data_t data;
	struct tree_node_t *lchild, *rchild;
}bitree_t;

bitree_t *CreateBitree(int i, bt_data_t a[], int n);

static int indent = 0;
static int step = 0;

int main()
{
	bt_data_t bt_array[] = {0, /* reserved [0] */
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'
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
	
	getchar();
	printf("----------------> step<%2d>, i=%d\n", step++, i);
	
	indent++;

	root = (bitree_t *)malloc(sizeof(bitree_t));
	root->data = a[i];
	printf("%*cRoot(%c)\n", indent, '-', root->data);
	
	j = 2 * i;
	if (j <= n) {
		/* must have left child */
		printf("%*cRoot(%d)->Left(%d)\n", indent, '-', i, j);
		root->lchild = CreateBitree(j, a, n);
	} else {
		printf("%*cRoot(%d)->Left(NULL)\n", indent, '-', i);
		root->lchild = NULL;
	}
	
	j = 2 * i + 1;
	if (j <= n) {
		/* must have right child */
		printf("%*cRoot(%d)->Right(%d)\n", indent, '-', i, j);
		root->rchild = CreateBitree(j, a, n);
	} else {
		printf("%*cRoot(%d)->Right(NULL)\n", indent, '-', i);
		root->rchild = NULL;
	}

	indent--;
	
	getchar();
	printf("<---------------- step<%2d>\n", step++);

	return root;
}
