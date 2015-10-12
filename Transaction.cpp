//
//  Transaction.cpp
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#include "Transaction.h"

Transaction::Transaction()
{
	failed = false;
}

Transaction::Transaction(char letter, string val1, string val2, string val3)
{
    switch (letter)
    {
        case 'O':
            command = 'O';
            lastName = val1;
            firstName = val2;
            accountNumber = val3;
            break;
            
        case 'D':
            command = 'D';
            accountNumber = val1;
            amount = val2;
            break;
            
        case 'W':
            command = 'W';
            accountNumber = val1;
            amount = val2;
            break;
            
        case 'T':
            command = 'T';
            accountNumber = val1;
            amount = val2;
            accountNumber2 = val3;
            break;
            
        case 'H':
            command = 'H';
            accountNumber = val1;
            break;
    }

	failed = false;
}



char Transaction::getCommand() const
{
    return command;
}

string Transaction::getAccountNumber() const
{
    return accountNumber;
}

string Transaction::getAmount() const
{
    return amount;
}

string Transaction::getAccountNumber2() const
{
    return accountNumber2;
}

string Transaction::getFirstName() const
{
    return firstName;
}

string Transaction::getLastName() const
{
    return lastName;
}

ostream& operator<<(ostream &outStream, const Transaction &transaction)
{
    switch(transaction.command)
    {
        case 'O':
            outStream << transaction.command << " " << transaction.lastName <<
            " " << transaction.firstName << " " << transaction.accountNumber;
            break;
            
        case 'D':
            outStream << transaction.command << " " << transaction.accountNumber <<
            " " << transaction.amount;
            break;
            
        case 'W':
            outStream << transaction.command << " " << transaction.accountNumber <<
            " " << transaction.amount;
            break;
    
        case 'T':
            outStream << transaction.command << " " << transaction.accountNumber <<
            " " << transaction.amount << " " << transaction.accountNumber2;
            break;
            
        case 'H':
            outStream << transaction.command << " " << transaction.accountNumber;
            break;
    }
    
    if(transaction.failed)
    {
        outStream << " (Failed)";
    }
    
    return outStream;
}

istream& operator>>(istream &inStream, Transaction &transaction)
{
    char command;
    string val1 = "", val2 = "", val3 = "";
    
    inStream >> command;
    
    switch(command)
    {
        case 'O':
            inStream >> val1 >> val2 >> val3;
            break;
            
        case 'D':
            inStream >> val1 >> val2;
            break;
            
        case 'W':
            inStream >> val1 >> val2;
            break;
            
        case 'T':
            inStream >> val1 >> val2 >> val3;
            break;
            
        case 'H':
            inStream >> val1;
            break;
    }
    
    transaction = Transaction(command, val1, val2, val3);
    return inStream;
    
}

void Transaction::operator=(const Transaction &transaction)
{
    switch (transaction.getCommand())
    {
        case 'O':
            command = 'O';
            lastName = transaction.lastName;
            firstName = transaction.firstName;
            accountNumber = transaction.accountNumber;
            break;
            
        case 'D':
            command = 'D';
            accountNumber = transaction.accountNumber;
            amount = transaction.amount;
            break;
            
        case 'W':
            command = 'W';
            accountNumber = transaction.accountNumber;
            amount = transaction.amount;
            break;
            
        case 'T':
            command = 'T';
            accountNumber = transaction.accountNumber;
            amount = transaction.amount;
            accountNumber2 = transaction.accountNumber2;
            break;
            
        case 'H':
            command = 'H';
            accountNumber = transaction.accountNumber;
            break;
    }
}

void Transaction::setFailed()
{
    failed = true;
}





