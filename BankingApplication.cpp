//
//  BankingApplication.cpp
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#include "BankingApplication.h"

BankingApplication::BankingApplication()
{
    root = nullptr;
}

BankingApplication::~BankingApplication()
{
    
}

bool BankingApplication::ReadTransactionFile(string fileName)
{
    return transactionQueue.BuildQueue(fileName);
}

void BankingApplication::ExecuteTransactions()
{
    Transaction *temp = new Transaction;
    
    while(!transactionQueue.isEmpty())
    {
        transactionQueue.Pop(temp);
        this->ExecuteTransCommand(temp);
    }
}

bool BankingApplication::InsertHelper(Node *currNode, ClientAccount *account)
{
    if(root == nullptr)
    {
        root = new Node;
        root->pAccount = account;
		root->right = nullptr;
		root->left = nullptr;
        return true;
    }
    
    Node *pNode = currNode;
    
    if(account->getAccountNumber() <= pNode->pAccount->getAccountNumber())
    {
        if(pNode->left == nullptr)
        {
            pNode->left = new Node;
			pNode->left->left = nullptr;
			pNode->left->right = nullptr;
            pNode->left->pAccount = account;
            return true;
        }
        else
        {
            InsertHelper(currNode->left, account);
        }
    }
    else
    {
        if(pNode->right == nullptr)
        {
            pNode->right = new Node;
			pNode->right->left = nullptr;
			pNode->right->right = nullptr;
            pNode->right->pAccount = account;
            return true;
        }
        else
        {
            InsertHelper(currNode->right, account);
        }
    }
    return false;
}


bool BankingApplication::Insert(ClientAccount *account)
{
    return InsertHelper(root, account);
}

bool BankingApplication::RetrieveHelper(Node *currNode, const ClientAccount &account, ClientAccount *&returnedAccount) const
{
    if(root == nullptr)
    {
        return false;
    }
    
    Node *pNode = currNode;
    
    if(currNode != nullptr)
    {
        if(*(pNode->pAccount) == account)
        {
            returnedAccount = pNode->pAccount;
            return true;
        }
        else
        {
            if(account.getAccountNumber() < pNode->pAccount->getAccountNumber())
            {
                RetrieveHelper(pNode->left, account, returnedAccount);
            }
            else
            {
                RetrieveHelper(pNode->right, account, returnedAccount);
            }
        }
    }
    else
    {
        return false;
    }
    if(returnedAccount != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BankingApplication::Retrieve(const ClientAccount &account, ClientAccount *&returnedAccount) const
{
    return RetrieveHelper(root, account, returnedAccount);
}

void BankingApplication::DisplayHelper(Node *currNode)
{
    if(root == nullptr)
    {
        cout << "ERROR: Banking application is empty." << endl;
        return;
    }
    
    Node *pNode = currNode;
    
    if(pNode->left != nullptr)
    {
        DisplayHelper(pNode->left);
    }
    cout << *(pNode->pAccount) << endl;
    
    if(pNode->right != nullptr)
    {
        DisplayHelper(pNode->right);
    }
}

void BankingApplication::Display()
{
    DisplayHelper(root);
}

void BankingApplication::Empty()
{
    
}

bool BankingApplication::isEmpty()
{
    if(root == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BankingApplication::ExecuteTransCommand(Transaction *transaction)
{
    if(transaction->getCommand() == 'O')
    {
        if(transaction->getAccountNumber().length() != 4)
        {
            cerr << "ERROR: Account number must be 4 integers long. Open account refused." << endl;
            return false;
        }
        else
        {
            this->OpenAccount(transaction->getLastName(), transaction->getFirstName(), transaction->getAccountNumber());
            return true;
        }
        
    }
    else if(transaction->getCommand() == 'D')
    {
        if(transaction->getAccountNumber().length() != 5)
        {
            cerr << "ERROR: Account number must be 5 integers long. Deposit refused." << endl;
            return false;
        }
        else
        {
            this->Deposit(transaction->getAccountNumber(), stoi(transaction->getAmount()));
            return true;
        }
    }
    else if(transaction->getCommand() == 'W')
    {
        if(transaction->getAccountNumber().length() != 5)
        {
            cerr << "ERROR: Account number must be 5 integers long. Withdrawal refused." << endl;
            return false;
        }
        else
        {
            this->Withdraw(transaction->getAccountNumber(), stoi(transaction->getAmount()));
            return true;
        }
    }
    else if(transaction->getCommand() == 'T')
    {
        if(transaction->getAccountNumber().length() != 5 || transaction->getAccountNumber2().length() != 5)
        {
            cerr << "ERROR: Account number must be 5 integers long. Transferal refused." << endl;
            return false;
        }
        else
        {
            this->Transfer(transaction->getAccountNumber(), stoi(transaction->getAmount()), transaction->getAccountNumber2());
            return true;
        }
        
    }
    else if(transaction->getCommand() == 'H')
    {
        if(transaction->getAccountNumber().length() > 5 || transaction->getAccountNumber().length() < 4)
        {
            cerr << "ERROR: Account number must be 4-5 integers long. History display refused." << endl;
            return false;
        }
        else
        {
            this->DisplayHistory(transaction->getAccountNumber());
            return true;
        }
    }
    else
    {
        cerr << "ERROR: Invalid command." << endl;
        return false;
    }
    return false;
    
}

bool BankingApplication::ExecuteCommand(char command, string val1, string val2, string val3)
{
    if(command == 'O')
    {
        if(val3.length() != 4)
        {
            cerr << "ERROR: Account number must be 4 integers long. Open account refused." << endl;
            return false;
        }
        else
        {
            this->OpenAccount(val1, val2, val3);
            return true;
        }
        
    }
    else if(command == 'D')
    {
        if(val1.length() != 5)
        {
            cerr << "ERROR: Account number must be 5 integers long. Deposit refused." << endl;
            return false;
        }
        else
        {
            this->Deposit(val1, stoi(val2));
            return true;
        }
    }
    else if(command == 'W')
    {
        if(val1.length() != 5)
        {
            cerr << "ERROR: Account number must be 5 integers long. Withdrawal refused." << endl;
            return false;
        }
        else
        {
            this->Withdraw(val1, stoi(val2));
            return true;
        }
    }
    else if(command == 'T')
    {
        if(val1.length() != 5 || val3.length() != 5)
        {
            cerr << "ERROR: Account number must be 5 integers long. Transferal refused." << endl;
            return false;
        }
        else
        {
            this->Transfer(val1, stoi(val2), val3);
            return true;
        }
        
    }
    else if(command == 'H')
    {
        if(val1.length() > 5 || val1.length() < 4)
        {
            cerr << "ERROR: Account number must be 4-5 integers long. History display refused." << endl;
            return false;
        }
        else
        {
            this->DisplayHistory(val1);
            return true;
        }
    }
    else
    {
        cerr << "ERROR: Invalid command." << endl;
        return false;
    }
    return false;
}

bool BankingApplication::Deposit(string number, int amount)
{
    if(number.length() != 5)
    {
        cerr << "ERROR: Account number must be 5 integers long. Deposit refused." << endl;
        return false;
    }
    else
    {
        ClientAccount *temp = nullptr;
        if(this->RetrieveByNumber(number.substr(0,4), temp))
        {
            temp->Deposit((int)(number.at(4) - '0'), amount);
            return true;
        }
        else
        {
            cerr << "ERROR: Account " + number.substr(0,4) + " not found. Deposit refused" << endl;
            return false;
        }
    }
}

bool BankingApplication::Withdraw(string number, int amount)
{
    if(number.length() != 5)
    {
        cerr << "ERROR: Account number is not 5 integers long. Withdrawal refused." << endl;
        return false;
    }
    else
    {
        ClientAccount *temp = nullptr;
        if(this->RetrieveByNumber(number.substr(0,4), temp))
        {
            temp->Withdraw((int)(number.at(4) - '0'), amount);
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool BankingApplication::Transfer(string sourceNumber, int amount, string destNumber)
{
    if(sourceNumber.substr(0,4) == destNumber.substr(0,4))
    {
        ClientAccount *temp = nullptr;
        if(this->RetrieveByNumber(sourceNumber.substr(0,4), temp))
        {
            temp->TransferWithinAccount((int)(sourceNumber.at(4) - '0'), amount, (int)(destNumber.at(4) - '0'));
            return true;
        }
        else
        {
            cerr << "ERROR: Account " + sourceNumber.substr(0,4) + " not found. Transferal refused." << endl;
            return false;
        }
    }
    else
    {
        ClientAccount *source = nullptr, *destination = nullptr;
        
        if(this->RetrieveByNumber(sourceNumber.substr(0,4), source) && this->RetrieveByNumber(destNumber.substr(0,4), destination))
        {
            source->TransferBetweenAccount((int)(sourceNumber.at(4) - '0'), amount, *destination, (int)(destNumber.at(4) - '0'));
            return true;
        }
        else
        {
            cerr << "ERROR: Account " + destNumber.substr(0,4) + " not found. Transferal refused." << endl;
            return false;
        }
    }
}

bool BankingApplication::DisplayHistory(string number)
{
    ClientAccount * temp = nullptr;
    if(RetrieveByNumber(number.substr(0,4), temp))
    {
        if(number.size() == 5)
        {
            temp->DisplayHistoryOfFund((int)(number.at(4) - '0'));
            return true;
        }
        else if(number.size() == 4)
        {
            temp->DisplayHistoryOfAllFunds();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool BankingApplication::OpenAccount(string lastName, string firstName, string number)
{
    ClientAccount *temp = nullptr;
    //cout << "this is the problem" << endl;
    if(number.size() == 4 && !this->RetrieveByNumber(number, temp))
    {
        ClientAccount *account = new ClientAccount(lastName, firstName, number);
        this->Insert(account);
        return true;
    }
    else
    {
        cerr << "ERROR: Account " + number + " is already open. Transaction refused." << endl;
        return false;
    }
}


bool BankingApplication::RetrieveByNumberHelper(Node *currNode, const string number, ClientAccount *&returnedAccount) const
{
    Node *pNode = currNode;
    
    if(root == nullptr)
    {
        return false;
    }
    else if(currNode != nullptr)
    {
        if((pNode->pAccount->getAccountNumber()) == number)
        {
            returnedAccount = pNode->pAccount;
            return true;
        }
        else
        {
            if(number < pNode->pAccount->getAccountNumber())
            {
                RetrieveByNumberHelper(pNode->left, number, returnedAccount);
            }
            else
            {
                RetrieveByNumberHelper(pNode->right, number, returnedAccount);
            }
        }
    }
    else
    {
        return false;
    }
    
    if(returnedAccount != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BankingApplication::RetrieveByNumber(const string number, ClientAccount *&returnedAccount) const
{
    return RetrieveByNumberHelper(root, number, returnedAccount);
}






