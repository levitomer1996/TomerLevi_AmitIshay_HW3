#pragma once


#define EXIT -1

typedef enum
{
	eShowSuperMarket, eAddProduct, eAddCustomer, eCustomerDoShopping,ePrintCart,eCustomerPay,eSortCustomer,eSearchCustomer,
	ePrintProductByType, eNofOptions
} eMenuOptions;

const char* menuStrings[eNofOptions];

int menu();