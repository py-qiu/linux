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

typedef int data_t;

/* use a cycle linked list w/o header node */
typedef struct node_t
{
	data_t data;
	struct node_t *next;
} linknode_t, *linklist_t;

int main()
{
	int i, n, m, k;
	linklist_t p, q;
	printf("total N people will join this suicide game, please input N:");
	scanf("%d", &n);
	printf( "people stand in a circle, assume everyone is assigned\n"
		"a sequence number from 1 to %d.\n"\
		"which one would you like to start the number off (1~%d):", n, n);
	scanf("%d", &k);
	printf("every Xth people should kill himself, please decide the X:");
	scanf("%d", &m);
	
	while(getchar() != '\n'); /* eat up extra \n */
	
	if (n < 1 || k > n || m < 1) {
		printf("input error!\n");
		return -1;
	}
	
	printf("game is starting ...\n");
	
	/* added the first one */
	p = q = (linklist_t)malloc(sizeof(linknode_t));
	p->data = 1;

	/* added left people */
	for (i = 2; i <= n; i++) {
		q->next = (linklist_t)malloc(sizeof(linknode_t));
		q = q->next;
		q->data = i;
	}
	/* complete the circle */
	q->next = p;
	
#if 0
	for (i=0; i<=N; i++) {
		printf("%d ", q->data);
		q = q->next;
	}
#endif
	
	/* 
	 * find the people ahead of #k
	 * (k-1)->(k)->(k+1)->(k+2)->(k+3)->(k+4)->(k+5)->(k+6)...
	 *  ^ step1: point to the pre-node of the k
	 * (k-1)->(k)->(k+1)->(k+2)->(k+3)->(k+4)->(k+5)->(k+6)...
	 *              ^ step2: hoop 2 steps and point to 
	 *                the pre-node of the one to be deleted
	 * (k-1)->(k)->(k+1)->(k+3)->(k+4)->(k+5)->(k+6)...
	 *              ^ step4 removed the m-th node and 
	 *                position still at the pre-node of 
	 *                next start point. goto step2 and 
	 *                continue the loop
	 */
	q = p;
	while (q->next != p)  //find the people ahead of k
	{
		if (q->next->data == k)
			break;
		q = q->next;
	}
	
	while (q->next != q) 
	{ /* till the last one */
		
		printf("continue? ");
		getchar();
		
		/* every m people */
		for (i = 0; i < m - 1; i++) {
			q = q->next;
		}
		
		/* kill the m-th people */
		p = q->next;
		q->next = p->next;
		printf("#%2d was killed\n", p->data);
		free(p);
	}
	
	/* kill the last one */
	printf("#%2d was killed\n", q->data);
	free(q);
	
	return 0;
}
