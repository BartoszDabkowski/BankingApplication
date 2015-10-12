//
//  TransactionQueue.h
//  Banking
//
//  Created by Bartosz Dabkowski on 11/30/14.
//  Copyright (c) 2014 Bartosz Dabkowski. All rights reserved.
//

#ifndef __Banking__TransactionQueue__
#define __Banking__TransactionQueue__

#include <stdio.h>


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

#include "ClientAccount.h"

using namespace std;

class TransactionQueue
{
public:
    TransactionQueue();
    ~TransactionQueue();
    
    bool BuildQueue(string fileName);
    bool Pop(Transaction *transaction);
    
    bool isEmpty();

private:
    queue<Transaction> transactions;
    
};

#endif /* defined(__Banking__TransactionQueue__) */
