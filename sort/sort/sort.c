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
 * 20150407	unicornx	added comments for partition()
 */
#include <stdio.h>

#include "datatype.h"
#include "linkstack.h"

#define N 8

void print(int s[], int n)
{
	int i = 0;
	for (i = 0; i < n; i++) {
		printf("%2d ", s[i]);
	}
	printf("\n");
}

void sort_select(int s[])
{
	int i, j, temp, min;

	for (i=0; i<N-1; i++)
	{
		min = i;
		for (j=i+1; j<N; j++)
		{
			if (s[j] < s[min]) min = j;
		}
		temp = s[i];
		s[i] = s[min];
		s[min] = temp;
	}

	return;
}

void sort_bubble(int s[])
{
	int i, j, temp, flag;

	for (i=N-1; i>=1; i--) {
		
		flag = 0;
		for (j=0; j<i; j++) {
			
			if (s[j] > s[j+1]) {
				temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
				flag = 1;
			}
		}
		/* if no swap happened, means the list has been sorted */
		if ( ! flag ) break;
	}

	return;
}


static int indent = 0;
/*
 * do partition
 * Input:
 *	s: data array input
 *	low: left boundary
 *	high: right boundary
 * Output:
 *	s: data array updated (swapped) after partition
 * Return:
 *	return position of pivot after partition
 */
int partition(int s[], int low, int high)
{
	/*
	 * i is defined as a pointer, which will iterate
	 * from the low/front to the high/rear before meeting j.
 	 *
 	 * j is defined as a pointer, which will iterate
	 * from the high/rear to the low/front before meeting i.
	 *
	 * pivot is used to backup the value of pivot before
	 * iterating.
	 */
	int i, j, pivot;
	
	printf ("%*c >partition [%d, %d] begin\n",
		2*indent, ' ', low, high);

	i = low;
	j = high;
	
	pivot = s[low]; /* select low as pivot and back it up */
	
	while (i < j) 
	{
		/* iterates may break if a swap would happen */
		while ((i < j) && (s[j] >= pivot)) 
			j--;

		if (i < j) 
		{
			printf("%*c >swap s[%d]<-s[%d], (%2d)<-(%2d): ",
				2*indent, ' ', i, j, s[i], s[j]);
			s[i] = s[j];
			
			print(s, N);
		}
		
		/* iterates may break if a swap would happen */
		while ((i < j) && (s[i] <= pivot)) 
			i++;

		if (i < j) {
			printf("%*c >swap s[%d]<-s[%d], (%2d)<-(%2d): ",
				2*indent, ' ', j, i, s[j], s[i]);
			s[j] = s[i];
			
			print(s, N);
		}
	}
	
	/*
	 * now the whole list is partitioned into two part
	 * all the items of which value are less than the pivot 
	 * are moved in front of the position of "i", all the 
	 * other items of which value are greater than the pivot
	 * are moved behind the position of "i".
	 * so finally restore value of pivot to the item at the 
	 * position of "i".
	 */
	s[i] = pivot;
	
	printf ("%*c >partition [%d, %d] done, restore pivot at (%d): ",
		2*indent, ' ', low, high, i);
	print(s, N);
	
	return i;
}

/*
 * quick sort by recurring
 * read http://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F 
 */
void sort_quick_r(int s[], int low, int high)
{
	int pivot; /* position of pivot after partition */
	
	indent++;
	
	printf("%*c->sort(low=%d, high=%d)\n",
		2*indent, ' ', low, high);

	pivot = partition(s, low, high);
		
	if ((pivot - 1) > low) 
	{
		sort_quick_r(s, low, pivot - 1);
	}

	if ((pivot + 1) < high)
	{
		sort_quick_r(s, pivot + 1, high);
	}

	printf("%*c<-sort(low=%d, high=%d)\n",
		2*indent, ' ', low, high);
	
	indent--;
	
	return;
}

/*
 * quick sort w/o recurring
 * for each cycle, after partition, push right-part (items
 * those value greater than that of pivot) into stack and
 * continue process left-part till there is no left-part
 * can be divided, then pop the delayed parts from the stack
 * and continue the cycle upon
 */
void  sort_quick(int s[], int low, int high)
{
	int i; /* position of pivot */
     	data_t  u;
     	linkstack_t *stack;
     	     	
     	stack = CreateEmptyLinkstack();
     	
     	u.low = low;  
     	u.high = high;  
     	PushStack(stack, u);
     	
     	while (0 == EmptyLinkstack(stack)) 
		{
     		PopStack(stack, &u);
        	low = u.low;
        	high = u.high;

			while (low < high) 
			{
	        		i  = partition(s, low, high);
            		if ((i + 1) < high) 
					{						
            			/*
            			 * there are items unsorted between
            			 * pivot and high, record this region
            			 * and push it into the stack and postpone
            			 * process for this region
            			 */
            			u.low = i + 1;
            			u.high = high;  
            			PushStack (stack, u); 
            		}
            		/* 
            		 * continue to process the region between low
            		 * and (pivot - 1)
            		 */
            		high = i - 1;
			}
		}
	
		DestroyLinkstack(stack);
}

int main()
{
	int s[N] = {50, 36, 35, 34, 33, 32, 31, 30};

	printf("before sort: ");
	print(s, N);
	
	//sort_select(s);
	//sort_bubble(s);
//	sort_quick_r(s, 0, N-1);
sort_quick(s, 0, N-1);

	printf("after sort : ");
	print(s, N);

	return 0;
}
