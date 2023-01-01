#pragma once


#define EXIT -1

typedef enum
{
	eShowSuperMarket, eAddProduct, eAddCustomer, eCustomerDoShopping,ePrintCart,eCustomerPay,eSortCustomer,
	ePrintProductByType, eNofOptions
} eMenuOptions;

const char* menuStrings[eNofOptions];

int menu();