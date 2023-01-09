#pragma once
#include "Address.h"
#include "Customer.h"
#include "Product.h"
#include "ShoppingCart.h"
#include "list.h"

typedef enum { SortedByName, SortedByShopTimes,SortedByTotalSpend, NotSorted, eNoOpt
} SORTOPTIONS;

typedef struct
{
	char*		name;
	Address		location;
	Customer*	customerArr;
	int			customerCount;
	LIST		products;
}SuperMarket;


int		initSuperMarket(SuperMarket* pMarket);
void	printSuperMarket(const SuperMarket* pMarket);
int		addProduct(SuperMarket* pMarket);
int		addNewProduct(SuperMarket* pMarket, const char* barcode);
int		addCustomer(SuperMarket* pMarket);
int		isCustomerInMarket(SuperMarket* pMarket, Customer* pCust);
int		doShopping(SuperMarket* pMarket);
Customer* doPrintCart(SuperMarket* pMarket);
int		doPayment(SuperMarket* pMarket);
Customer*		getCustomerShopPay(SuperMarket* pMarket);
void fillCart(SuperMarket* pMarket, ShoppingCart* pCart);

void	printProductByType(SuperMarket* pMarket);
void	printAllProducts(const SuperMarket* pMarket);
void	printAllCustomers(const SuperMarket* pMarket);
void	sortCustomers(SuperMarket* pMarket);

int		getProductIndexByBarcode(SuperMarket* pMarket, const char* barcode);
Product* getProductByBarcode(SuperMarket* pMarket, const char* barcode);
Product* getProductFromUser(SuperMarket* pMarket, char* barcode);
void	getUniquBarcode(char* barcode, SuperMarket* pMarket);
Customer* FindCustomerByName(SuperMarket* pMarket, const char* name);

Customer* getCustomerWhoShop(SuperMarket* pMarket);
Product* getProductAndCount(SuperMarket* pMarket, int* pCount);

void	freeMarket(SuperMarket* pMarket);

void printSortEnum(SORTOPTIONS op);
Customer* searchBCustomer(SuperMarket* pMarket);
Customer* searchBCustomerByName(SuperMarket* pMarket, char* name);
Customer* searchBCustomerByShoppingTimes(SuperMarket* pMarket, int times);
Customer* searchBCustomerByTotalSpent(SuperMarket* pMarket, float totalSpent);