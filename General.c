#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "General.h"



char* getStrExactLength(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	getsStrFixSize(temp, MAX_STR_LEN, msg);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char*	getsStrFixSize(char* buffer, int size, const char* msg)
{
	puts(msg);
	return myGets(buffer, size);
}

char*  myGets(char* buffer, int size)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, stdin))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char**	splitCharsToWords(char* str, int* pCount, const char* del, int* pTotalLength)
{
	char* word;
	int count = 0;
	char* temp = _strdup(str);
	*pTotalLength = 0;
	char** wordsArray = NULL;

	word = strtok(temp, del);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, del);
	}
	*pCount = count;
	free(temp);
	return wordsArray;
}

float	getPositiveFloat(const char* msg)
{
	float val;
	do {
		puts(msg);
		scanf("%f", &val);
	} while (val < 0);
	return val;
}

int		getPositiveInt(const char* msg)
{
	int val;
	do {
		puts(msg);
		scanf("%d", &val);
	} while (val < 0);
	return val;
}

int		countCharInString(const char* str, char tav)
{
	int count = 0;
	while (*str)
	{
		if (*str == tav)
			count++;
		str++;
	}
	return count;
}

int		checkEmptyString(char* str)
{
	while (*str)
	{
		if (!isspace(*str))
			return 0;
		str++;
	}
	return 1;
}

void makeASort(SuperMarket* pMarket)
{
	sortCustomers(pMarket);
}

int getNumOfProducts(NODE* productHead)
{
	int count = 0;
	NODE* temp = productHead;
	while (temp != NULL) {
		temp = temp->next;
		count++;
	}
	return count - 1;
}

Product** getProductsAsArray(SuperMarket* pMarket)
{
	NODE* temp = &pMarket->products.head;
	Product** pArray =(Product**) malloc(sizeof(Product*));
	if (!pArray&& !temp) {
		return NULL;
	}
	int count = 0;
	while (!temp)
	{
		pArray[count++] = temp->key;
		temp = temp->next;
	}
	return pArray;
}

int isPaid(SuperMarket* pMarket)
{
	for (int i = 0; i < pMarket->customerCount; i++) {
		if (pMarket->customerArr[i].pCart != NULL) {
			return 0;
		}
	}
	return 1;
}

void searchCustomer(SuperMarket* pMarket)
{
	Customer* pCust = searchBCustomer(pMarket);
	if (pCust) {
		printCustomer(pCust);
	}
	
}

const void* generalArrayFunction(const void* array, int arraySize, size_t elementSize, void(f)(void* element))
{
	for (int i = 0; i < arraySize; i++)
	{
		f((char*)array + i * elementSize);
	}
}



