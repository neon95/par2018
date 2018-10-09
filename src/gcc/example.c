/*=============================================================================
# Filename: example.c
# Author: bookug
# Mail: bookug@qq.com
# Last Modified: 2018-10-09 08:13
# Description: union two sorted lists, and apply the sqrt operator on each item
# For debug, gcc -lm -g example.c -o example
# To release, gcc -O2 -lm example.c -o example
=============================================================================*/

#include <stdio.h>
#include <math.h> 
#include <stdlib.h> 

typedef struct MyNode
{
	int val;
	struct MyNode* next;
}Node;
Node* result_head = NULL;
Node* result_tail = NULL;
void addResult(int _val)
{
	/*printf("check %d\n",_val);*/
	Node* t = (Node*)malloc(sizeof(Node));
	t->val = _val;
	t->next = NULL;
	//add the new node to the tail
	if(result_head == NULL)
	{
		result_head = t;
		result_tail = result_head;
	}
	else
	{
		result_tail->next = t;
		result_tail = t;
	}
}

//NOTICE: sqrt(8) works but sqrt(n) must be compiled by -lm
int main(int argc, const char* argv[])
{
	int list1[] = {1,3,5,7};
	int list1_num = 4;
	int list2[] = {2,4,6,8};
	int list2_num = 4;

	int pos1 = 0, pos2 = 0;
	//NOTICE: this strategy not always fails, for example, the final elements of the two lists are the same
	while(pos1 < list1_num && pos2 < list2_num)
	{
		/*printf("check %d %d\n", pos1, pos2);*/
		if(list1[pos1] < list2[pos2])
		{
			addResult(list1[pos1]);
			pos1++;
		}
		else if(list1[pos1] > list2[pos2])
		{
			addResult(list2[pos2]);
			pos2++;
		}
		else   //equal case, only add once
		{
			addResult(list1[pos1]);
			pos1++;
			pos2++;
		}
	}

	//output each item in result after sqrt operation
	Node* p = result_head;
	while(p != NULL)
	{
		double r = sqrt((double)(p->val));
		printf("%lf\n", r);
		p = p->next;
	}

	//release the result list
	p = result_head;
	//NOTICE: another bug exists here, but error is not reported when running
	printf("%p %p\n", result_head, result_tail);
	while(p != NULL)
	{
		free(p);
		p = p->next;
		printf("%p\n", p);
	}

	return 0;
}

