


#ifndef _LIST_
#define _LIST_

#include "def.h"

typedef struct node
{
	DATA			key;
	struct node* next;
}NODE;

typedef struct
{
	NODE head;
}LIST;




BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value, int compare(const void*, const void*));	// add new node after *pNode

BOOL L_delete(NODE* pNode, BOOL isFree);					// erase node after *pNode

NODE* L_find(NODE* pNode, DATA Value, int compare(const void*, const void*));		// return a pointer to the node 

BOOL L_free(LIST* pList);					// free list memory

int L_print(LIST* pList, void print(const void*));					// print the list content

#endif
