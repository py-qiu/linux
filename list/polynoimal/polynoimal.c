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
 * 20141110	unicornx	updated sort_insert & iterate_list
 * 20150508	unicornx	improved the demo print
 */
#include <stdio.h>
#include <stdlib.h>

#include "datatype.h"
#include "linklist.h"

#define DEMO 7

#if DEMO == 1

/*
 * case1:
 * a = x
 * b = x^2
 */
data_t case_a[1] = {{1, 1}};
data_t case_b[1] = {{1, 2}};

#elif DEMO == 2

/*
 * case2:
 * a = x^2
 * b = x
 */
data_t case_a[] = {{1, 2}};
data_t case_b[] = {{1, 1}};

#elif DEMO == 3

/*
 * case3:
 * a = x
 * b = x
 */
data_t case_a[] = {{1, 1}};
data_t case_b[] = {{1, 1}};

#elif DEMO == 4

/*
 * case4:
 * a = x
 * b = -x
 */
data_t case_a[] = {{1, 1}};
data_t case_b[] = {{-1, 1}};

#elif DEMO == 5

/*
 * case5:
 * a = x^3 + x
 * b = x^4 + x^2 + 1
 */
data_t case_a[] = {{1, 3}, {1, 1}};
data_t case_b[] = {{1, 4}, {1, 2}, {1, 0}};
	
#elif DEMO == 6

/*
 * case6:
 * a = x^4 + x^3 + x^2 + x + 1
 * b = x^3 + x
 */
data_t case_a[] = {{1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0}};
data_t case_b[] = {{1, 3}, {1, 1}};

#elif DEMO == 7

/*
 * case7:
 * a = x^4 - x^3 + x^2 + x
 * b = x^5 + x^3 + x + 1
 */
data_t case_a[] = {{1, 4}, {-1, 3}, {1, 2}, {1, 1}};
data_t case_b[] = {{1, 5}, {1, 3}, {1, 1}, {1, 0},};

#endif /* DEMO */

linklist_t	list_a, list_b;
int		pos_a, pos_b;

/* declaration of functions */
void sort_insert(linklist_t, linknode_t *);
void iterate_list(linklist_t);

void print_lists()
{
	printf("polynoimal a = "); iterate_list(list_a);
	printf("%*c%c\n", 15 + 8 * pos_a, ' ', '^');
	printf("polynoimal b = "); iterate_list(list_b);
	printf("%*c%c\n", 15 + 8 * pos_b, ' ', '^');
}

int main()
{
	linklist_t q;
	
	list_a = CreateEmptyLinklist();
	if (NULL == list_a) {
		printf("CreateEmptyLinklist error\n");
		return 1;
	}
	list_b = CreateEmptyLinklist();
	if (NULL == list_b) {
		printf("CreateEmptyLinklist error\n");
		DestroyLinklist(list_b);
		return 1;
	}
	
	/* 
	 * Assume NO duplicated items with same exp 
	 * existing in the polynoimal
	 */
#if DEMO == 0
	printf("input polynominal_1: <coef,exp>\n");
	while (scanf("%d,%d", &data.coef, &data.exp) == 2){
		q = (linklist_t)malloc(sizeof(linknode_t));
		q->data = data;
		q->next = NULL;
		sort_insert(list_a, q);
	}
	
	while(getchar() != '\n'); /* eat up extra \n */
	
	printf("input polynominal_2: <coef,exp>\n");
	while (scanf("%d,%d", &data.coef, &data.exp) == 2) {
		q = (linklist_t)malloc(sizeof(linknode_t));
		q->data = data;
		q->next = NULL;
		sort_insert(list_b, q);
	}
#else
	int i;
	for (i = 0; i < sizeof(case_a)/sizeof(data_t); i++) {
		q = (linklist_t)malloc(sizeof(linknode_t));
		q->data = case_a[i];
		q->next = NULL;
		sort_insert(list_a, q);
	}

	for (i = 0; i < sizeof(case_b)/sizeof(data_t); i++) {
		q = (linklist_t)malloc(sizeof(linknode_t));
		q->data = case_b[i];
		q->next = NULL;
		sort_insert(list_b, q);
	}
#endif
	/* items in the set have been sorted in descenting */
	
	print_lists();
		
	struct node_t	*node_a, *node_b;
	
	node_a = list_a->next;
	node_b = list_b->next;
	pos_a = pos_b = 0;
	
	while (node_a != NULL && node_b != NULL) {
		if (node_b->data.exp > node_a->data.exp ) {
			
			printf("====== b[%d].exp > a[%d].exp\n", pos_b, pos_a);
			
			InsertLinklist(list_a, pos_a, node_b->data);
			/* node_a is not changed, only updated the pos_a */
			pos_a++;
			
			node_b = node_b->next;
			pos_b++;
			
		} else if (node_b->data.exp < node_a->data.exp) {
			
			printf("====== b[%d].exp < a[%d].exp\n", pos_b, pos_a);
			
			node_a = node_a->next;
			pos_a++;
			
		} else {
			printf("====== b[%d].exp == a[%d].exp\n", pos_b, pos_a);
				
			node_a->data.coef += node_b->data.coef;
			
			node_a = node_a->next;
			pos_a++;
			
			node_b = node_b->next;
			pos_b++;
		}
		
		print_lists();
	}
	
	/* 
	 * the items remains in list b all have the exponent less than 
	 * that of the items in list a, just append them to list a
	 */
	printf("====== merge remaining items in list b into list a\n");
	while (NULL != node_b) {
		InsertLinklist(list_a, pos_a, node_b->data);
		node_b = node_b->next;
		pos_a++;
	}
	print_lists();
	
	printf("====== remove items in list a whose coef equal to zero\n");
	/* remove those items left whose coef equal to zero */
	node_a = list_a->next;
	pos_a = 0;
	while (node_a != NULL) {
		if (0 == node_a->data.coef) {
			/* move to the next before delete */
			node_a = node_a->next; 
			DeleteLinklist(list_a, pos_a);
			
		} else {
			node_a = node_a->next;
			pos_a++;
		}
	}
	printf("polynoimal final = ");
	iterate_list(list_a);

	DestroyLinklist(list_a);
	DestroyLinklist(list_b);
	
	return 0;
}

/*
 * sort and insert the element in descending with exponent
 */
void sort_insert(linklist_t list, linknode_t *p)
{
	while (list->next != NULL && list->next->data.exp  > p->data.exp)
		list = list->next;
	p->next = list->next;
	list->next = p;

	return;
}

void iterate_list(linklist_t list)
{
	linknode_t *node;
	
	if (!list) return;
	
	/* start from the first element */
	node = list->next;
	while (NULL != node) {
		printf("%d*X^%d + ", node->data.coef, node->data.exp);
		
		/* move to the next */
		node = node->next;
	}
	
	if (LengthLinklist(list) > 0)
		printf("\b\b\b   \n");
	else
		printf("\n");
}
