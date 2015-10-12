//
//  Fund.cpp
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#include "Fund.h"

Fund::Fund()
{
    
}

Fund::Fund(int number, string name)
{
    fundName = name;
    fundNumber = number;
    balance = 0;
}

string Fund::getFundName() const
{
    return fundName;
}

int Fund::getFundNumber() const
{
    return fundNumber;
}

int Fund::getBalance() const
{
    return balance;
}

bool Fund::Deposit(int const amount)
{
    if(amount < 0)
    {
        cout << "ERROR: cannot deposit negative amount. Deposit refused." << endl;
        return false;
    }
    else
    {
        balance += amount;
        return true;
    }
}
bool Fund::Withdraw(int const amount)
{
    if (amount < 0)
    {
        cout << "ERROR: cannot withdraw negative amount. Withdrawal refused." << endl;
        return false;
    }
    else if(amount > balance)
    {
        return false;
    }
    else
    {
        balance -= amount;
        return true;
    }
}

void Fund::InsertHistory(Transaction transaction)
{
    transactions.push_back(transaction);
}

ostream& operator<<(ostream &outStream, const Fund &fund)
{
    outStream << fund.fundName << ": $" << fund.balance << endl;
    
    for(int i = 0; i < fund.transactions.size(); i++)
    {
        outStream << "   " << fund.transactions[i] << endl;
    }
    
    return outStream;
}

bool Fund::isTransactionEmpty() const
{
    return transactions.empty();
}













