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

#include "datatype.h"
#include "bitree.h"
#include "linkqueue.h"

bitree_t *CreateBitree(int i, bt_data_t data[], int n)
{
	bitree_t *root;
	int j;
	
	root = (bitree_t *)malloc(sizeof(bitree_t));
	root->data = data[i];
	
	j = 2 * i;
	if (j <= n && data[j] != NULL_DATA) {
		/* must have left child */
		root->lchild = CreateBitree(j, data, n);
	} else {
		/* no left child */
		root->lchild = NULL;
	}
	
	j = 2 * i + 1;
	if (j <= n && data[j] != NULL_DATA) {
		/* must have right child */
		root->rchild = CreateBitree(j, data, n);
	} else {
		/* no right child */
		root->rchild = NULL;
	}

	return root;
}

void PreOrder(bitree_t *root)
{
	if (NULL == root) return;
	
	printf("%c ", root->data);
	
	PreOrder(root->lchild);
	
	PreOrder(root->rchild);

	return;
}

void InOrder(bitree_t *root)
{
	if (NULL == root) return;
	
	InOrder(root->lchild);
	
	printf("%c ", root->data);
	
	InOrder(root->rchild);

	return;
}

void PostOrder(bitree_t *root)
{
	if (NULL == root) return;
	
	PostOrder(root->lchild);
	
	PostOrder(root->rchild);
	
	printf("%c ", root->data);
	
	return;
}

void NoOrder(bitree_t *root)
{
	linkqueue_t *lq;
	
	/* create queue */
	lq = CreateEmptyLinkqueue();
	
	/* root node enters queue */
	EnQueue(lq, root);
	
	while (!EmptyLinkqueue(lq)) {
		
		DeQueue(lq, (data_t *)(&root));
		printf("%c ", root->data);
		
		if (root->lchild != NULL) {
			EnQueue(lq, root->lchild);
		}
		
		if (root->rchild != NULL) {
			EnQueue(lq, root->rchild);
		}
	}

	return;
}


