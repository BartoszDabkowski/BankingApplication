//
//  BankingApplication.h
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#ifndef __Banking__BankingApplication__
#define __Banking__BankingApplication__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

#include "ClientAccount.h"
#include "TransactionQueue.h"

using namespace std;

class BankingApplication
{
public:
    BankingApplication();
    ~BankingApplication();
    
    bool Insert(ClientAccount *account);
    bool Retrieve(const ClientAccount &account, ClientAccount *&returnedAccount) const;
    bool RetrieveByNumber(const string number, ClientAccount *&returnedAccount) const;
    void Display();
    void Empty();
    bool isEmpty();
    
    bool ReadTransactionFile(string fileName);
    void ExecuteTransactions();
    
    bool ExecuteTransCommand(Transaction *transaction);
    bool ExecuteCommand(char command, string val1, string val2, string val3);
    
private:
    struct Node
    {
        ClientAccount *pAccount;
        Node *right;
        Node *left;
    };
    
    Node *root;
    TransactionQueue transactionQueue;
    
    bool Deposit(string number, int amount);
    bool Withdraw(string number, int amount);
    bool Transfer(string sourceNumber, int amount, string destNumber);
    bool DisplayHistory(string number);
    bool OpenAccount(string lastName, string firstName, string number);
    
    bool InsertHelper(Node *currNode, ClientAccount *account);
    bool RetrieveHelper(Node *currNode, const ClientAccount &account, ClientAccount *&returnedAccount) const;
    void DisplayHelper(Node *currNode);
    bool RetrieveByNumberHelper(Node *currNode, const string number, ClientAccount *&returnedAccount) const;
};

#endif /* defined(__Banking__BankingApplication__) */
