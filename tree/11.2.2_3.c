/*************************************************************************
    > File Name: 11.2.2_3.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 12 May 2015 11:13:37 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct node_t
{
	char data;
	struct	node_t *lchild;
	struct	node_t *rchild;
}btree_t;

void tree_init(btree_t **tree)
{
	*tree = (btree_t *)malloc(sizeof(btree_t));
	(*tree)->lchild = (*tree)->rchild = NULL;
	(*tree)->data = 0;
}

void construct(char data, btree_t **node)
{
	btree_t *temp_node = *node;

	while(temp_node)
	{
		if (!temp_node->data)
		{
			temp_node->data = data;
			break;
		}
		else if (data<=temp_node->data)
		{
			if(!temp_node->lchild)
			{
				tree_init(&temp_node->lchild);
				temp_node->lchild->data = data;
				break;
			}
			else
			{
				temp_node = temp_node->lchild;
				continue;
			}
		}
		else if(data>temp_node->data)
		{
			if(!temp_node->rchild)
			{
				tree_init(&temp_node->rchild);
				temp_node->rchild->data = data;
				break;
			}
			else
			{
				temp_node = temp_node->rchild;
				continue;
			}

		}
	}

	return;
}

int main()
{
	int i;
	btree_t *root;
	char data[8] = {'e', 'f', 'h', 'g', 'a', 'c', 'b', 'd'};
	tree_init(&root);
	for(i=0; i<8; i++)
	{
		construct(data[i], &root);
	}

	return 0;
}
