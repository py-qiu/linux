/*************************************************************************
    > File Name: mytree.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 12 May 2015 01:51:42 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef char bt_data_t;

typedef struct tree_node_t
{
	bt_data_t data;
	struct tree_node_t *lchild, *rchild;
}bitree_t;

extern int pre_order(bitree_t *tree);
extern int post_order(bitree_t *tree);
extern int in_order(bitree_t *tree);

bitree_t *CreateBitree(int i, bt_data_t a[], int n);

int main()
{
//	bt_data_t bt_array[] = {0,'a','b','e',0,'c',0,'f',0,0,'d',0,0,0,'g',0,0,0,0,0,0,0,0,0,0,0,0,0,'h','i'};

	bt_data_t bt_array[] = {0, 'A', 'B', 'C', 'D', 'E', 0, 'F', 0, 0, 'G', 'H', 0, 0, 'I'};
	bitree_t *root;

	root = CreateBitree(1, bt_array, sizeof(bt_array)/sizeof(bt_data_t)-1);
	
	printf("先序:");
	pre_order(root);

	printf("\n");
	printf("中序:");
	in_order(root);

	printf("\n");
	printf("后序:");
	post_order(root);

	printf("\n");

	return 0;
}

bitree_t *CreateBitree(int i, bt_data_t a[], int n)
{
	bitree_t *root;
	int j = 0;

	root = (bitree_t *)malloc(sizeof(bitree_t));

	root->data = a[i];

	j = 2 * i;

	if ((j<=n) && (0!=a[j]))
	{
		root->lchild = CreateBitree(j, a, n);
	}
	else
	{
		root->lchild = NULL;
	}

	j = 2 * i + 1;

	if ((j<=n) && (0!=a[j]))
	{
		root->rchild = CreateBitree(j, a, n);
	}
	else
	{
		root->rchild = NULL;
	}

	return root;
}



