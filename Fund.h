//
//  Fund.h
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#ifndef __Banking__Fund__
#define __Banking__Fund__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>


#include "Transaction.h"

using namespace std;

class Fund
{
    friend ostream& operator<<(ostream &outStream, const Fund &fund);
    
public:
    Fund();
    Fund(int number, string name);
    
    string getFundName() const;
    int getFundNumber() const;
    int getBalance() const;
    
    bool Deposit(int const amount);
    bool Withdraw(int const amount);
    
    bool isTransactionEmpty() const;
    
    void InsertHistory(Transaction transaction);
    
private:
    string fundName;
    int fundNumber;
    int balance;
    vector<Transaction> transactions;
};

#endif /* defined(__Banking__Fund__) */
