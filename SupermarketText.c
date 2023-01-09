#define _CRT_SECURE_NO_WARNINGS
#include "SupermarketText.h"
#define TEXT_FILE "Customers.txt"

int writeCustomerToTextFile(FILE* fp, Customer* pCust)
{
	if (!fp || !pCust) return 0;
	fprintf(fp, "%s\n", pCust->name);
	fprintf(fp, "%d\t", pCust->shopTimes);
	fprintf(fp, "%f\n", pCust->totalSpend);
	return 1;
}

int writeCustomerArrToTextFile(Customer* custArr, int count)
{
	FILE* fp;
	fp = fopen(TEXT_FILE, "w");
	if (!fp)
		return 0;

	fprintf(fp, "%d\n", count);

	for (int i = 0; i < count; i++) {
		if (!writeCustomerToTextFile(fp, &custArr[i])) {
			return 0;
		};
	}

	fclose(fp);
	return 1;
}

int readCustomerFromTextFile(FILE* fp, Customer* pCust)
{
	pCust->name = malloc(20);
	if (fscanf(fp, "%s\n", pCust->name) != 1) {
		return 0;
	}if (fscanf(fp, "%d\t", &pCust->shopTimes) != 1) {
		return 0;
	}
	if (fscanf(fp, "%f\n", &pCust->totalSpend) != 1) {
		return 0;
	}	
	return 1;
}

int readCustomerArrFromTextFile(SuperMarket* pMarket)
{
	FILE* fp;
	fp = fopen(TEXT_FILE, "r");
	if (!fp) {
		return 0;
	}
	if (fscanf(fp, "%d", &pMarket->customerCount) != 1)
	{
		fclose(fp);
		return 0;
	}
	pMarket->customerArr = (Customer*)malloc(sizeof(Customer) * pMarket->customerCount);
	if (!pMarket->customerArr) return 0;
	for (int i = 0; i < pMarket->customerCount; i++)
	{
	readCustomerFromTextFile(fp, &pMarket->customerArr[i]);
		pMarket->customerArr[i].pCart = NULL;
	}
	return 1;
}
