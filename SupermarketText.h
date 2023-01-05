#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Supermarket.h"
//Write
int writeCustomerToTextFile(FILE* fp, Customer* pCust);
int writeCustomerArrToTextFile(Customer* custArr,int count);
//Read
int readCustomerFromTextFile(FILE* fp, Customer* pCust);
int readCustomerArrFromTextFile(SuperMarket* pMarket);