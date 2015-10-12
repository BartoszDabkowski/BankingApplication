//
//  Transaction.h
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#ifndef __Banking__Transaction__
#define __Banking__Transaction__


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class Transaction
{
    friend ostream& operator<<(ostream &outStream, const Transaction &transaction);
    friend istream& operator>>(istream &inStream, Transaction &transaction);
    
public:
    Transaction();
    Transaction(char letter, string val1, string val2, string val3);
    
    char getCommand() const;
    string getAccountNumber() const;
    string getAmount() const;
    string getAccountNumber2() const;
    string getFirstName() const;
    string getLastName() const;
    
    
    void setFailed();
    
    void operator=(const Transaction &transaction);
    
    
private:
    char command;
    string accountNumber;
    string amount;
    string accountNumber2;
    string firstName;
    string lastName;
    bool failed;
};

#endif /* defined(__Banking__Transaction__) */
