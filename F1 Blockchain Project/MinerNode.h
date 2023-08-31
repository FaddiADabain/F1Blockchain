#ifndef MINERNODE_H
#define MINERNODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Blockchain.h"
#include "Miner.h"
#include "MemoryPool.h"

using namespace std;

class MinerNode {
private:
    string publicKey;
    Blockchain& blockchain;
    MemoryPool& memoryPool;
    bool miningActive;

public:
    MinerNode(const string& publicKey, Blockchain& blockchain, MemoryPool& memoryPool);
    void startMining();
    void stopMining();
    void addTransactionToMemoryPool(const Transaction& transaction);
    void clearMemoryPool();
    void saveBlockchainToFile();
    void readTransactionsFromFile();
    void printBlockchain();
};

#endif
