#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Supermarket.h"
#include "Product.h"
#include "Customer.h"
#include "Address.h"
#include "General.h"
#include "ShoppingCart.h"

const char* sortOptions[eNoOpt] = { "Sorted by name", "Sorted by shop time",
								"Sorted by money spent" };

int		initSuperMarket(SuperMarket* pMarket)
{
	pMarket->customerCount = 0;
	pMarket->customerArr = NULL;
	L_init(&pMarket->products);
	pMarket->name = getStrExactLength("Enter market name");
	return initAddress(&pMarket->location);
}

void	printSuperMarket(const SuperMarket* pMarket)
{
	printf("Super Market Name: %s\t", pMarket->name);
	printf("Address: ");
	printAddress(&pMarket->location);
	printf("\n");
	printAllProducts(pMarket);
	printf("\n");
	printAllCustomers(pMarket);
}

int		addProduct(SuperMarket* pMarket)
{
	char barcode[BARCODE_LENGTH + 1];
	getBorcdeCode(barcode);

	if (!addNewProduct(pMarket, barcode)) {
		return 0;
	}
	return 1;
}

int		addNewProduct(SuperMarket* pMarket,const char* barcode)
{

	
	Product* pProd = (Product*)calloc(1, sizeof(Product));
	if (!pProd) {
		return 0;
	}
	strcpy(pProd->barcode, barcode);
	initProductNoBarcode(pProd);
	if (L_insert(&pMarket->products.head, pProd, compareProductsByBarcode)) {
		return 1;
	}
	return 0;
}

int		addCustomer(SuperMarket* pMarket)
{
	Customer cust;
	if (!initCustomer(&cust))
		return 0;

	if (isCustomerInMarket(pMarket, &cust))
	{
		printf("This customer already in market\n");
		free(cust.name);
		return 0;
	}

	pMarket->customerArr = (Customer*)realloc(pMarket->customerArr, (pMarket->customerCount + 1) * sizeof(Customer));
	if (!pMarket->customerArr)
	{
		free(cust.name);
		return 0;
	}

	pMarket->customerArr[pMarket->customerCount] = cust;
	pMarket->customerCount++;
	return 1;
}

int		isCustomerInMarket(SuperMarket* pMarket, Customer* pCust)
{
	for (int i = 0; i < pMarket->customerCount; i++)
	{
		if (strcmp(pMarket->customerArr[i].name, pCust->name) == 0)
			return 1;
	}
	return 0;
}

int	doShopping(SuperMarket* pMarket)
{
	Customer* pCustomer = getCustomerShopPay(pMarket);
	if (!pCustomer)
		return 0;

	if (pCustomer->pCart == NULL)
	{
		pCustomer->pCart = (ShoppingCart*)malloc(sizeof(ShoppingCart));
		if (!pCustomer->pCart)
			return 0;
		initCart(pCustomer->pCart);
	}
	fillCart(pMarket, pCustomer->pCart);
	printf("---------- Shopping ended ----------\n");
	return 1;
}

Customer*	doPrintCart(SuperMarket* pMarket)
{
	Customer* pCustomer = getCustomerShopPay(pMarket);
	if (!pCustomer)
		return NULL;
	if (pCustomer->pCart == NULL)
	{
		printf("Customer cart is empty\n");
		return NULL;
	}
	printShoppingCart(pCustomer->pCart);
	return pCustomer;
}

int	doPayment(SuperMarket* pMarket)
{
	Customer* pCustomer = doPrintCart(pMarket);
	if(!pCustomer)
		return 0;
	pay(pCustomer);
	return 1;
}

Customer*	getCustomerShopPay(SuperMarket* pMarket)
{
	if (pMarket->customerCount == 0)
	{
		printf("No customer listed to market\n");
		return NULL;
	}

	if (&pMarket->products.head == NULL)
	{
		printf("No products in market - cannot shop\n");
		return NULL;
	}

	Customer* pCustomer = getCustomerWhoShop(pMarket);
	if (!pCustomer)
	{
		printf("this customer not listed\n");
		return NULL;
	}

	return pCustomer;
}

void	printAllProducts(const SuperMarket* pMarket)
{
	
	printf("%-20s %-10s\t", "Name", "Barcode");
	printf("%-20s %-10s %s\n", "Type", "Price", "Count In Stoke");
	printf("--------------------------------------------------------------------------------\n");
	L_print(&pMarket->products,printProduct);
	
}

void	printAllCustomers(const SuperMarket* pMarket)
{
	printf("There are %d listed customers\n", pMarket->customerCount);
	for (int i = 0; i < pMarket->customerCount; i++)
		printCustomer(&pMarket->customerArr[i]);
}

void sortCustomers(SuperMarket* pMarket)
{
	if (pMarket->customerCount == 0) {
		printf("Super market got no customers! \n");
		return;
	}
	int choice = 0;
	printf("How would you like to sort the customers: \n");

	for (int i = 0; i < eNoOpt - 1 ; i++) {
		printf("%d ) %s \n",i , sortOptions[i]);
	}
	scanf_s("%d", &choice);
	
	switch (choice)
	{
	case SortedByName:
		qsort(pMarket->customerArr, pMarket->customerCount, sizeof(Customer), comapreCustomerByName);
		
		break;
	case SortedByShopTimes:
		qsort(pMarket->customerArr, pMarket->customerCount, sizeof(Customer), comapreCustomerByShopTimes);
		break;
	case SortedByTotalSpend:
		qsort(pMarket->customerArr, pMarket->customerCount, sizeof(Customer), comapreCustomerByTotalSpend);
		break;
	default:
		break;
	}
	printf("Customers %s \n", sortOptions[choice]);
	printAllCustomers(pMarket);
}


Customer* getCustomerWhoShop(SuperMarket* pMarket)
{
	printAllCustomers(pMarket);
	char name[MAX_STR_LEN];
	getsStrFixSize(name, sizeof(name), "Who is shopping? Enter cutomer name\n");

	Customer* pCustomer = FindCustomerByName(pMarket, name);
	
	return pCustomer;
}


void fillCart(SuperMarket* pMarket,ShoppingCart* pCart)
{
	printAllProducts(pMarket);
	char op;
	while (1)
	{
		printf("Do you want to shop for a product? y/Y, anything else to exit!!\t");
		do {
			scanf("%c", &op);
		} while (isspace(op));
		getchar(); //clean the enter
		if (op != 'y' && op != 'Y')
			break;
		int count;
		Product* pProd = getProductAndCount(pMarket, &count);
		if(pProd)
		{
			if (!addItemToCart(pCart, pProd->barcode, pProd->price, count))
			{
				printf("Error adding item\n");
				return;
			}
			pProd->count -= count; //item bought!!!
		}
	}
}

Product* getProductAndCount(SuperMarket* pMarket, int* pCount)
{
	char barcode[BARCODE_LENGTH + 1];
	Product* pProd = getProductFromUser(pMarket, barcode);
	if (pProd == NULL)
	{
		printf("No such product\n");
		return NULL;
	} 
	
	if (pProd->count == 0)
	{
		printf("This product out of stock\n");
		return NULL;
	}
	
	int count;
	do {
		printf("How many items do you want? max %d\n", pProd->count);
		scanf("%d", &count);
	} while (count <= 0 || count > pProd->count);
	*pCount = count;
	return pProd;
}

void	printProductByType(SuperMarket* pMarket)
{
	if (&pMarket->products.head == NULL)
	{
		printf("No products in market\n");
		return;
	}
	eProductType	type = getProductType();
	int count = 0;
	
}

Product* getProductFromUser(SuperMarket* pMarket, char* barcode)
{
	getBorcdeCode(barcode);
	return getProductByBarcode(pMarket, barcode);
}

void	freeMarket(SuperMarket* pMarket)
{
	
}

void printSortEnum(SORTOPTIONS op)
{
	switch (op)
	{
	case SortedByName:
		printf("Sort by name \n");
		break;
	case SortedByShopTimes:
		printf("Sort by shop times \n");
		break;
	case SortedByTotalSpend:
		printf("Sort by money spent \n");
		break;
	default:
		break;
	}
}

void	getUniquBarcode(char* barcode, SuperMarket* pMarket)
{
	int cont = 1;
	while (cont)
	{
		getBorcdeCode(barcode);
		int index = getProductIndexByBarcode(pMarket, barcode);
		if (index == -1)
			cont = 0;
		else
			printf("This product already in market\n");
	}
}

int getProductIndexByBarcode(SuperMarket* pMarket, const char* barcode)
{
	

}


Product* getProductByBarcode(SuperMarket* pMarket, const char* barcode)
{
	Product tempP;
	strcpy(tempP.barcode, barcode);
	NODE* p = L_find(pMarket->products.head.next, &tempP, compareProductsByBarcode);
	return p ? p->key : NULL;
}

Customer* FindCustomerByName(SuperMarket* pMarket, const char* name)
{
	for (int i = 0; i < pMarket->customerCount; i++)
	{
		if (isCustomer(&pMarket->customerArr[i], name))
			return &pMarket->customerArr[i];
	}
	return  NULL;
}
