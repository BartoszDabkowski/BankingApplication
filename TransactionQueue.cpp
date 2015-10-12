//
//  TransactionQueue.cpp
//  Banking
//
//  Created by Bartosz Dabkowski on 11/30/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#include "TransactionQueue.h"

TransactionQueue::TransactionQueue()
{

}

TransactionQueue::~TransactionQueue()
{
    while(!transactions.empty())
    {
        transactions.pop();
    }
    
}

bool TransactionQueue::BuildQueue(string fileName)
{
    ifstream infile(fileName);
    if (!infile) {
        cout << "File could not be opened." << endl;
        return false;
    }
    
    while(!infile.eof())
    {
        Transaction *newAccount = new Transaction;
        infile >> *newAccount;
        transactions.push(*newAccount);
    }
    return true;
}

bool TransactionQueue::isEmpty()
{
    if(transactions.empty())
    {
        cout << endl << "Proccessing Done. Final Balances" << endl << endl;
        return true;
    }
    else
    {
        return false;
    }
    
}

bool TransactionQueue::Pop(Transaction *transaction)
{
    if(transactions.empty())
    {
        return false;
    }
    else
    {
        *transaction = transactions.front();
        transactions.pop();
        return true;
    }
}






