#pragma once
#include <stdio.h>
#include "Supermarket.h"
#include "General.h"
#include "list.h"

//Write
int writeSuperMarketToBFile(const SuperMarket* sm);
int writeProductToBFile(const Product* prod, FILE* file);
int writeProductArrToBFile(FILE* file, LIST* node, int count);
int writeAddressToBFile(const SuperMarket* sm, FILE* file);

//Read
int readSuperMarketFromBFile(SuperMarket* sm);
int readProductFromBFile(FILE* file, Product* p);
int readProductArrFromBFile(const char* file, SuperMarket* pMarket);
int readAddressFromBFile(SuperMarket* sm, const FILE* file);