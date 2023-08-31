#include "MemoryPool.h"

void MemoryPool::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

const vector<Transaction>& MemoryPool::getTransactions() const {
    return transactions;
}

void MemoryPool::clear() {
    transactions.clear();
}