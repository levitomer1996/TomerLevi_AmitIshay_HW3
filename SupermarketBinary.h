#pragma once
#include <stdio.h>
#include "Supermarket.h"
#include "General.h"
#include "list.h"

//Write
int writeSuperMarketToBFile(const SuperMarket* sm);
int writeProductToBFile(const Product* prod, FILE* file);
int writeProductArrToBFile(FILE* file, NODE* head, int count);
int writeAddressToBFile(const SuperMarket* sm, const FILE* file);

//Read
int readSuperMarketFromBFile(SuperMarket* sm);
int readProductFromBFile(FILE* file, Product* p);
int readProductArrFromBFile(const char* file, SuperMarket* pMarket, int* pCount);
int readAddressFromBFile(SuperMarket* sm, const FILE* file);