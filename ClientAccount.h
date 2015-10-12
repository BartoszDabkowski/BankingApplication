//
//  ClientAccount.h
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#ifndef __Banking__ClientAccount__
#define __Banking__ClientAccount__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

#include "Fund.h"
#include "Transaction.h"

using namespace std;

static const int MAX_FUNDS = 10;

class ClientAccount
{
    friend ostream& operator<<(ostream &outStream, const ClientAccount &account);
    
public:
    ClientAccount();
    ClientAccount(string last, string first, string account);
    void InitializeFunds();
    
    string getFirstName() const;
    string getLastName() const;
    string getAccountNumber() const;
    
    bool Deposit(int const number, int const amount);
    bool Withdraw(int const number, int const amount);
    bool TransferWithinAccount(int const sourceNumber, int const amount, int const destNumber);
    bool TransferBetweenAccount(int const sourceNumber, int const amount, ClientAccount &account, int const destNumber);
    
    void DisplayHistoryOfFund(int number) const;
    void DisplayHistoryOfAllFunds() const;
    
    bool operator==(const ClientAccount &account) const;
    void operator=(const ClientAccount &account);
    
    
private:
    string firstName;
    string lastName;
    string accountNumber;
    Fund clientFunds[MAX_FUNDS];
    vector<Transaction> errors;
};

#endif /* defined(__Banking__ClientAccount__) */
