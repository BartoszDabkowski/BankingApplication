//
//  ClientAccount.cpp
//  Banking
//
//  Created by Bartosz Dabkowski on 11/29/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#include "ClientAccount.h"

ClientAccount::ClientAccount()
{
    InitializeFunds();
}
ClientAccount::ClientAccount(string last, string first, string account)
{
    lastName = last;
    firstName = first;
    accountNumber = account;
    InitializeFunds();
}

void ClientAccount::InitializeFunds()
{
    clientFunds[0] = Fund(0, "Money Market");
    clientFunds[1] = Fund(1, "Prime Money Market");
    clientFunds[2] = Fund(2, "Long-Term Bond");
    clientFunds[3] = Fund(3, "Short-Term Bond");
    clientFunds[4] = Fund(4, "500 Index Fund");
    clientFunds[5] = Fund(5, "Capital Value Fund");
    clientFunds[6] = Fund(6, "Growth Equity Fund");
    clientFunds[7] = Fund(7, "Growth Index Fund");
    clientFunds[8] = Fund(8, "Value Fund");
    clientFunds[9] = Fund(9, "Value Stock Index");
}

string ClientAccount::getFirstName() const
{
    return firstName;
}

string ClientAccount::getLastName() const
{
    return lastName;
}

string ClientAccount::getAccountNumber() const
{
    return accountNumber;
}


bool ClientAccount::Deposit(int const number, int const amount)
{
    if(clientFunds[number].Deposit((amount)))
    {
        Transaction transaction = Transaction('D', accountNumber + to_string(number), to_string(amount), "");
        clientFunds[number].InsertHistory(transaction);
        return true;
    }
    else
    {
        return false;
    }
}

bool ClientAccount::Withdraw(int const number, int const amount)
{
    if(clientFunds[number].Withdraw((amount)))
    {
        Transaction transaction = Transaction('W', accountNumber + to_string(number), to_string(amount), "");
        clientFunds[number].InsertHistory(transaction);
        return true;
    }
//Money Market____________________________________________________________________________________________________________________
    else if(number == 0 && amount > clientFunds[0].getBalance())
    {
        int maxAmount = clientFunds[0].getBalance();
        int amountOtherAccount = amount - maxAmount;
        
        if(amountOtherAccount > clientFunds[1].getBalance())
        {
            cerr << "ERROR: Not enough funds to withdraw " + to_string(amount) +" from " + firstName + " "
            + lastName + " " + clientFunds[number].getFundName() << endl;
            Transaction transaction = Transaction('W', accountNumber + to_string(number), to_string(amount), "");
            transaction.setFailed();
            clientFunds[number].InsertHistory(transaction);
            return false;
        }
        else
        {
            this->Withdraw(0, maxAmount);
            this->Withdraw(1, amountOtherAccount);
            
            return true;
        }
    }
//Prime Money Market___________________________________________________________________________________________________________________
    else if(number == 1 && amount > clientFunds[1].getBalance())
    {
        int maxAmount = clientFunds[1].getBalance();
        int amountOtherAccount = amount - maxAmount;
        
        if(amountOtherAccount > clientFunds[0].getBalance())
        {
            cerr << "ERROR: Not enough funds to withdraw " + to_string(amount) +" from " + firstName + " "
            + lastName + " " + clientFunds[number].getFundName() << endl;
            Transaction transaction = Transaction('W', accountNumber + to_string(number), to_string(amount), "");
            transaction.setFailed();
            clientFunds[number].InsertHistory(transaction);
            return false;
        }
        else
        {
            this->Withdraw(1, maxAmount);
            this->Withdraw(0, amountOtherAccount);
            
            return true;
        }
    }
//Long-term Bond_________________________________________________________________________________________________________________________
    else if(number == 2 && amount > clientFunds[2].getBalance())
    {
        int maxAmount = clientFunds[2].getBalance();
        int amountOtherAccount = amount - maxAmount;
        
        if(amountOtherAccount > clientFunds[3].getBalance())
        {
            cerr << "ERROR: Not enough funds to withdraw " + to_string(amount) +" from " + firstName + " "
            + lastName + " " + clientFunds[number].getFundName() << endl;
            Transaction transaction = Transaction('W', accountNumber + to_string(number), to_string(amount), "");
            transaction.setFailed();
            clientFunds[number].InsertHistory(transaction);
            return false;
        }
        else
        {
            this->Withdraw(2, maxAmount);
            this->Withdraw(3, amountOtherAccount);
            return true;
        }
    }
//Short-term bond_________________________________________________________________________________________________________________________
    else if(number == 3 && amount > clientFunds[3].getBalance())
    {
        int maxAmount = clientFunds[3].getBalance();
        int amountOtherAccount = amount - maxAmount;
        
        if(amountOtherAccount > clientFunds[2].getBalance())
        {
            cerr << "ERROR: Not enough funds to withdraw " + to_string(amount) +" from " + firstName + " "
            + lastName + " " + clientFunds[number].getFundName() << endl;
            Transaction transaction = Transaction('W', accountNumber + to_string(number), to_string(amount), "");
            transaction.setFailed();
            clientFunds[number].InsertHistory(transaction);
            return false;
        }
        else
        {
            this->Withdraw(3, maxAmount);
            this->Withdraw(2, amountOtherAccount);
            return true;
        }
    }
//____________________________________________________________________________________________________________________________________________
    else
    {
        cerr << "ERROR: Not enough funds to withdraw " + to_string(amount) +" from " + firstName + " "
        + lastName + " " + clientFunds[number].getFundName() << endl;
        Transaction transaction = Transaction('W', accountNumber + to_string(number), to_string(amount), "");
        transaction.setFailed();
        clientFunds[number].InsertHistory(transaction);
        
        return false;
    }
}

bool ClientAccount::TransferWithinAccount(int const sourceNumber, int const amount, int const destNumber)
{
    if (amount < 0)
    {
        cout << "ERROR: cannot transfer negative amount. Transferal refused." << endl;
        return false;
    }
    else if(clientFunds[sourceNumber].Withdraw((amount)))
    {
        clientFunds[destNumber].Deposit((amount));
        Transaction transaction = Transaction('T', accountNumber + to_string(sourceNumber), to_string(amount), accountNumber
                                              + to_string(destNumber));
        clientFunds[sourceNumber].InsertHistory(transaction);
        clientFunds[destNumber].InsertHistory(transaction);
        return true;
    }
    else
    {
        Transaction transaction = Transaction('T', accountNumber + to_string(sourceNumber), to_string(amount), accountNumber
                                              + to_string(destNumber));
        transaction.setFailed();
        clientFunds[sourceNumber].InsertHistory(transaction);
        clientFunds[destNumber].InsertHistory(transaction);
        return false;
    }
}

bool ClientAccount::TransferBetweenAccount(int const sourceNumber, int const amount, ClientAccount &account, int const destNumber)
{
    if(clientFunds[sourceNumber].Withdraw((amount)))
    {
        account.clientFunds[destNumber].Deposit((amount));
        Transaction transaction = Transaction('T', accountNumber + to_string(sourceNumber), to_string(amount), accountNumber
                                              + to_string(destNumber));
        clientFunds[sourceNumber].InsertHistory(transaction);
        account.clientFunds[destNumber].InsertHistory(transaction);
        return true;
    }
    else
    {
        Transaction transaction = Transaction('T', accountNumber + to_string(sourceNumber), to_string(amount), accountNumber
                                              + to_string(destNumber));
        transaction.setFailed();
        clientFunds[sourceNumber].InsertHistory(transaction);
        account.clientFunds[destNumber].InsertHistory(transaction);
        return false;
    }
    
}

void ClientAccount::DisplayHistoryOfFund(int number) const
{
    cout << "Transaction History for " << firstName << " " << lastName << " "
    << clientFunds[number].getFundName() << ": $" << clientFunds[number].getBalance() << endl;
    cout << clientFunds[number];
}

void ClientAccount::DisplayHistoryOfAllFunds() const
{
    cout << "Transaction History for " << firstName << " " << lastName << " by fund." << endl;
    for(int i = 0; i < MAX_FUNDS; i++)
    {
        if (!clientFunds[i].isTransactionEmpty())
        {
            cout << clientFunds[i];
        }
        else
        {
            //don't print;
        }
    }
    cout << endl;
}

bool ClientAccount::operator==(const ClientAccount &account) const
{
    return (this->lastName == account.lastName) && (this->firstName == account.firstName) && (this->accountNumber == account.accountNumber);
}

void ClientAccount::operator=(const ClientAccount &account)
{
    this->firstName = account.firstName;
    this->lastName = account.lastName;
    this->accountNumber = account.accountNumber;
}

ostream& operator<<(ostream &outStream, const ClientAccount &account)
{
    outStream << account.firstName << " " << account.lastName << " Account ID: " << account.accountNumber << endl;
    
    for(int i = 0; i < MAX_FUNDS; i++)
    {
        outStream << "   " << account.clientFunds[i].getFundName() << ": $" <<account.clientFunds[i].getBalance() << endl;
    }
    
    return outStream;
}