#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "General.h"
#include "Supermarket.h"
#include "SupermarketBinary.h"
#include "SupermarketText.h"




int menu();



const char* menuStrings[eNofOptions] = { "Show SuperMarket", "Add Product",
								"Add Customer", "Customer Shopping","Print Shopping Cart","Customer Pay","Sort Customers","Search Customers",
								"Print Product By Type"};

int main()
{
	
	SuperMarket	market;
	
	int isBinExist = readSuperMarketFromBFile(&market); 
	 readCustomerArrFromTextFile(&market);
	if (!isBinExist ) {
		if (!initSuperMarket(&market))
		{
			printf("error init  Super Market");
			return 0;
		}
	}

	int option;
	int stop = 0;
	
	do
	{
		option = menu();

		switch (option)
		{
		case eShowSuperMarket:
			printSuperMarket(&market);
			break;


		case eAddProduct:
			if (!addProduct(&market))
				printf("Error adding product\n");
			break;

		case eAddCustomer:
			if (!addCustomer(&market))
				printf("Error adding customer\n");
			break;

		case eCustomerDoShopping:
			if(!doShopping(&market))
				printf("Error in shopping\n");
			break;
		case ePrintCart:
			doPrintCart(&market);
			break;

		case eCustomerPay:
			if(!doPayment(&market))
				printf("Error in payment\n");
			break;
		case eSortCustomer:
			makeASort(&market);
			break;
		case eSearchCustomer:
			searchCustomer(&market);
			break;
		case ePrintProductByType:
			printProductByType(&market);
			break;

		case EXIT:
			if (!isPaid(&market)) {
				printf("It seems like not everyone paid.\n");
				break;
			}else{
				printf("Bye bye\n");
				stop = 1;
				break;
			}
		

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	writeSuperMarketToBFile(&market);
	writeCustomerArrToTextFile(market.customerArr, market.customerCount);
	freeMarket(&market);
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i, menuStrings[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

