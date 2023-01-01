
/*   list.c   */
/**************/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL L_init(LIST * pList)
{
	if (pList == NULL) return False;	// no list to initialize

	pList->head.next = NULL;
	return True;
}


/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, DATA Value, int compare(const void*, const void*))
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));

	if (temp == NULL || pNode == NULL) {
		return NULL;
	}
	NODE* current = pNode;
	NODE* prev = NULL;
	temp->key = Value;
	while (current && compare(&current->key, &temp->key) > 0) {
		prev = current;
		current = current->next;
	}
	temp->next = current;
	if (prev == NULL) {
		pNode = temp;
	}
	else {
		prev->next = temp;
	}

	return temp;

}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
BOOL L_delete(NODE* pNode, BOOL isFree)
{
	NODE* temp;

	if (!pNode || !(temp = pNode->next)) return False;

	pNode->next = temp->next;
	if (isFree) {
		free(temp);
	}

	return True;
}


/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
NODE* L_find(NODE* pNode, DATA Value, int compare(const void*, const void*))
{
	NODE* temp = pNode;
	while (temp != NULL)
	{
		if (compare(temp->key, Value) == 0)
			return temp;
		temp = temp->next;
	}

	return NULL;
}


////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
BOOL L_free(LIST* pList)
{
	NODE* tmp;

	if (!pList) return False;

	for (tmp = &(pList->head); L_delete(tmp, True); );
	return True;
}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
int L_print(LIST* pList, void print(const void*))
{
	NODE* tmp;
	int		c = 0;

	if (!pList) return 0;

	printf("\n");
	for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
		print(tmp->key);
	printf("\n");
	return c;
}