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
#ifndef __BITREE_H__
#define __BITREE_H__

#include "datatype.h"

typedef struct tree_node_t {
	bt_data_t 		data;
	struct tree_node_t 	*lchild, *rchild;
} bitree_t;

/*
 * create the whole bi-tree
 * Input:
 * 	i: index of root node
 * 	data: array stores the data of B-tree
 * 	n: total number of nodes 
 * Output:	void
 * Return:	the tree created
 */
bitree_t *CreateBitree(int i, bt_data_t data[], int n);

/*
 * iterate the bi-tree by pre-order
 * Input:
 *	root:	root of the tree.
 * Output:	void
 * Return:	void
 */
void PreOrder(bitree_t *root);

/*
 * iterate the bi-tree by in-order
 * Input:
 *	root:	root of the tree.
 * Output:	void
 * Return:	void
 */
void InOrder(bitree_t *root);

/*
 * iterate the bi-tree by post-order
 * Input:
 *	root:	root of the tree.
 * Output:	void
 * Return:	void
 */
void PostOrder(bitree_t *root);

/*
 * iterate the bi-tree by level
 * Input:
 *	root:	root of the tree.
 * Output:	void
 * Return:	void
 */
void NoOrder(bitree_t *root);

#endif
