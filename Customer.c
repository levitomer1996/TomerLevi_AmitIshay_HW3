#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Customer.h"
#include "General.h"

int	initCustomer(Customer* pCustomer)
{

	do {
		pCustomer->name = getStrExactLength("Enter customer name\n");
		if (!pCustomer->name)
			return 0;
	} while (checkEmptyString(pCustomer->name));
	pCustomer->shopTimes = 0;
	pCustomer->totalSpend = 0;
	pCustomer->pCart = NULL;
	return 1;
}

void	printCustomer(const Customer* pCustomer)
{
	printf("Name: %s\t, times shopped: %d,\t total spent: %f ", pCustomer->name,pCustomer->shopTimes,pCustomer->totalSpend);
	
	if (pCustomer->pCart == NULL)
		printf("Shopping cart is empty!\n");
	else 
	{
		printf("Doing shopping now!!!\n");
		//printShoppingCart(pCustomer->pCart);
	}
}


void	pay(Customer* pCustomer)
{
	if (!pCustomer->pCart)
		return;
	printf("---------- Cart info and bill for %s ----------\n", pCustomer->name);
	pCustomer->totalSpend += printShoppingCart(pCustomer->pCart);
	pCustomer->shopTimes++;
	printf("!!! --- Payment was recived!!!! --- \n");
	freeShoppingCart(pCustomer->pCart);
	free(pCustomer->pCart);
	pCustomer->pCart = NULL;
}




int isCustomer(const Customer* pCust, const char* name)
{
	if (strcmp(pCust->name, name) == 0)
		return 1;
	return 0;
}

void	freeCustomer(Customer* pCust)
{
	if (pCust->pCart)
		pay(pCust); //will free every thing
	free(pCust->name);
}

int comapreCustomerByName(void* v1, void* v2)
{
	Customer* c1 = (Customer*)v1;
	Customer* c2 = (Customer*)v2;
	return strcmp(c1->name, c2->name);
}

int comapreCustomerByShopTimes(void* v1, void* v2)
{
	Customer* c1 = (Customer*)v1;
	Customer* c2 = (Customer*)v2;
	if (c1->shopTimes > c2->shopTimes) return -1;
	else if (c1->shopTimes < c2->shopTimes) return 1;
	else return 0;
}

int comapreCustomerByTotalSpend(void* v1, void* v2)
{
	Customer* c1 = (Customer*)v1;
	Customer* c2 = (Customer*)v2;
	if (c1->totalSpend < c2->totalSpend) {
		return 1;
	}
	else if (c1->totalSpend > c2->totalSpend) {
		return -1;
	}
	else {
		return 0;
	}
}



