#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SupermarketBinary.h"




int writeSuperMarketToBFile(const SuperMarket* sm)
{
	FILE* fp = fopen("Supermarket.bin", "wb");
	if (fp == NULL)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	int name_len = (int)strlen(sm->name) + 1;
	if (fwrite(&name_len, sizeof(int), 1, fp) != 1) {
		return 0;
	}
		
	if (fwrite(sm->name, sizeof(char), name_len, fp) != name_len) {
		return 0;
	}
	//writeProductArrToBFile(fp,&sm->products.head,getNumOfProducts(&sm->products.head));
	writeAddressToBFile(sm, fp);
	writeProductArrToBFile(fp,&sm->products.head,getNumOfProducts(&sm->products.head));
	fclose(fp);
}

int writeProductToBFile(const Product* prod, FILE* file)
{
	if (fwrite(prod->name, sizeof(char), NAME_LENGTH + 1, file) != NAME_LENGTH + 1) {
		return 0;
	}
	if (fwrite(prod->barcode, sizeof(char), BARCODE_LENGTH + 1, file) != BARCODE_LENGTH + 1) {
		return 0;
	}
	if (fwrite(&prod->price, sizeof(float), 1, file) != 1) {
		return 0;
	}
	if (fwrite(&prod->count, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (fwrite(&prod->type, sizeof(eProductType), 1, file) != 1) {
		return 0;
	}
}

int writeProductArrToBFile(FILE* file, NODE* head, int count)
{
	
	if (!file || !head)
		return 0;
	if (fwrite(&count, sizeof(int), 1, file) != 1)
	{
		fclose(file);
		return 0;
	}
	NODE* temp = head;
	while (temp != NULL) {
		if (!writeProductToBFile(&temp->key, file))
		{
			fclose(file);
			return 0;
		}
		temp = temp->next;
	}
	return 1;
}

int writeAddressToBFile(const SuperMarket* sm,  FILE* file)
{
	//street
	int len_street = (int)strlen(sm->location.street) + 1;
	if (fwrite(&len_street, sizeof(int), 1, file) != 1)
		return 0;
	if (fwrite(sm->location.street, sizeof(char), len_street, file) != len_street)
		return 0;
	//houseNumber
	
	if (fwrite(&sm->location.num, sizeof(int), 1, file) != 1)
		return 0;
	//city
	int len_city = (int)strlen(sm->location.city) + 1;
	if (fwrite(&len_city, sizeof(int), 1, file) != 1)
		return 0;
	if (fwrite(sm->location.city, sizeof(char), len_city, file) != len_city)
		return 0;
	return 1;
}
int readAddressFromBFile(SuperMarket* sm, const FILE* file)
{
	//street
	int len_street;
	if (fread(&len_street, sizeof(int), 1, file) != 1) {
		return 0;
	}
	sm->location.street = (char*)malloc(len_street * sizeof(char));

	if (!sm->location.street) {
		return 0;
	}
	

	if (fread(sm->location.street,  sizeof(char), len_street, file) != len_street)
	{
		free(&sm->location.street);
		return 0;
	}
	printf("%s \n", sm->location.street);
	
	if (fread(&sm->location.num, sizeof(int), 1, file) != 1)
	{
		return 0;
	}
	//city
	int len_city;
	if (fread(&len_city, sizeof(int), 1, file) != 1)
		return 0;
	sm->location.city = (char*)malloc(len_city * sizeof(char));

	if (!(sm->location.city)) {
		return 0;
	}
	if (fread(sm->location.city, sizeof(char), len_city, file) != len_city)
	{
		free(&sm->location.city);
		return 0;
	}
	printf("%s", sm->location.city);
	return 1;
}

int readSuperMarketFromBFile(SuperMarket* sm)
{
	FILE* fp = fopen("Supermarket.bin", "rb");
	
	int len;
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	sm->name = (char*)malloc(len * sizeof(char));

	if (!sm->name) {
		return 0;
	}
	if (fread(sm->name, sizeof(char), len, fp) != len)
	{
		free(sm->name);
		return 0;
	}
	readAddressFromBFile(sm,fp);
	readProductArrFromBFile(fp, sm);
	printf("%s \n", sm->name);
	
	// close file
	fclose(fp);

	return 1;

}

int readProductFromBFile(FILE* file, Product* p)
{
	*p->name = malloc(sizeof(char)*(NAME_LENGTH + 1));
	if (fread(p->name, sizeof(char), NAME_LENGTH + 1, file) != NAME_LENGTH + 1)
	{
		return 0;
	}
	printf("%s", p->name);
	*p->barcode = malloc(sizeof(char) * (BARCODE_LENGTH + 1));
	if (fread(p->barcode, sizeof(char), BARCODE_LENGTH + 1, file) != BARCODE_LENGTH + 1)
	{
		return 0;
	}
	printf("%s", p->barcode);
	if (fread(&p->count, sizeof(int), 1, file) !=  1)
	{
		return 0;
	}
	if (fread(&p->price, sizeof(float), 1, file) != 1)
	{
		return 0;
	}
	if (fread(&p->type, sizeof(eProductType), 1, file) != 1)
	{
		return 0;
	}
	return 1;
}

int readProductArrFromBFile(const char* file,SuperMarket* pMarket)
{
	int count;
	if (fread(&count, sizeof(int), 1, file) != 1) {
		return 0;
	}
	if (!L_init(&pMarket->products)) {
		return 0;
	};

	for (int i = 0; i < count; i++)
	{
		Product* pProd =(Product*) malloc(sizeof(Product));
		if (!readProductFromBFile(file,pProd))
		{
		
			fclose(file);
			return 0;
		}
		if (!L_insert(&pMarket->products.head, pProd, compareProductsByBarcode)) {
			return 0;
		}
		printProduct(pProd);
	}
	return 1;
}


