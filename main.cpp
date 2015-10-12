//
//  main.cpp
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

#include "BankingApplication.h"

int main()
{
    BankingApplication Chase = BankingApplication();
    
    Chase.ReadTransactionFile("BankTrans.txt");
    Chase.ExecuteTransactions();
    Chase.Display();

	int input;
	do
	{
		cout << "Enter 0 to exit" << endl;
		cin >> input;
	}
	while(input != 0);

    return 0;
}
