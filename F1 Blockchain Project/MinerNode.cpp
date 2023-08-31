#include "MinerNode.h"
#include "Blockchain.h"
#include "Miner.h"
#include "MemoryPool.h"
#include "transaction_utils.h"
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

MinerNode::MinerNode(const string& publicKey, Blockchain& blockchain, MemoryPool& memoryPool)
    : publicKey(publicKey), blockchain(blockchain), memoryPool(memoryPool), miningActive(false) {
}

void MinerNode::printBlockchain() {
    vector<Block> chain = blockchain.getChain();
    Block lastBlock = chain.back();

    cout << "Index: " << lastBlock.index << endl;
    cout << "Nonce: " << lastBlock.nonce << endl;
    cout << "Timestamp: " << lastBlock.timestamp << endl;
    cout << "Data: " << lastBlock.data << endl;
    cout << "Previous Hash: " << lastBlock.previousHash << endl;
    cout << "Current Hash: " << lastBlock.currentHash << endl;
    cout << endl;
}

void MinerNode::addTransactionToMemoryPool(const Transaction& transaction) {
    memoryPool.addTransaction(transaction);
}

void MinerNode::clearMemoryPool() {
    memoryPool.clear();
}

void MinerNode::readTransactionsFromFile() {
    string line;
    ifstream transactions_file("transactions.txt");

    if (transactions_file.is_open()) {
        while (getline(transactions_file, line)) {
            Transaction transaction = parseTransaction(line);
            addTransactionToMemoryPool(transaction);
        }
        transactions_file.close();

        // Remove the transactions from the file after reading them
        ofstream clear_transactions_file("transactions.txt", ios::trunc);
        clear_transactions_file.close();
    }
    else {
        cout << "Unable to open transactions file." << endl;
    }
}

void MinerNode::startMining() {
    while (true) {
        readTransactionsFromFile();
        vector<Transaction> transactions = memoryPool.getTransactions();

        for (const auto& transaction : transactions) {
            mine(transaction, blockchain);
        }

        clearMemoryPool();  // Clear the memory pool after mining the transactions

        saveBlockchainToFile();  // Call the function to save the entire blockchain to the file
        printBlockchain();

        // Sleep for a while before trying to mine transactions again
        this_thread::sleep_for(chrono::seconds(5));
    }
}

void MinerNode::stopMining() {
    miningActive = false;
}

void MinerNode::saveBlockchainToFile() {
    ofstream file;
    file.open("results.txt", ios::out | ios::trunc);

    if (file.is_open()) {
        for (const auto& block : blockchain.getChain()) {
            file << block.toString() << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to open the file." << endl;
    }
}