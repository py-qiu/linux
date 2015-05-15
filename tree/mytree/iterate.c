/*************************************************************************
    > File Name: iterate.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 12 May 2015 03:53:40 PM CST
 ************************************************************************/

#include<stdio.h>

typedef char bt_data_t;

typedef struct tree_node_t
{
	bt_data_t data;
	struct tree_node_t *lchild, *rchild;
}bitree_t;


int pre_order(bitree_t *tree)
{
	if (!tree)
		return 1;

	printf("%c ", tree->data);
	pre_order(tree->lchild);
	pre_order(tree->rchild);

	return 0;
}

int post_order(bitree_t *tree)
{
	if (!tree)
		return 1;

	post_order(tree->lchild);
	post_order(tree->rchild);

	printf("%c ", tree->data);

	return 0;
}

int in_order(bitree_t *tree)
{
	if (!tree)
		return 1;
	in_order(tree->lchild);

	printf("%c ", tree->data);

	in_order(tree->rchild);

	return 0;
}

