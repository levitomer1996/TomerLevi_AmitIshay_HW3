#include "Supermarket.h"
#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255


char*		getStrExactLength(const char* msg);
char*		getsStrFixSize(char* buffer, int size, const char* msg);
char*		myGets(char* buffer, int size);
char*		getDynStr(char* str);
char**		splitCharsToWords(char* str, int* pCount, const char* del, int* pTotalLength);

float		getPositiveFloat(const char* msg);
int			getPositiveInt(const char* msg);
int			countCharInString(const char* str, char tav);
int			checkEmptyString(char* str);
void		makeASort(SuperMarket* pMarket);

int			getNumOfProducts(NODE* productHead);
Product**	getProductsAsArray(SuperMarket* pMarket);
int			isPaid(SuperMarket* pMarket);

void		searchCustomer(SuperMarket* pMarket);
#endif

