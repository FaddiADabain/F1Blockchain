#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <vector>
#include "transaction_utils.h"

using namespace std;

class MemoryPool {
private:
    vector<Transaction> transactions;

public:
    void addTransaction(const Transaction& transaction);
    const vector<Transaction>& getTransactions() const;
    void clear();
};

#endif
