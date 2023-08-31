#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <thread>
#include <chrono>
#include "Blockchain.h"
#include "MinerNode.h"
#include "MemoryPool.h"
#include "Wallet.h"
#include "KeyGeneration.h"

using namespace std;

void simulateIncomingTransactions(const string& transactionsFile, int transactionCount) {
    ofstream transactions_file(transactionsFile, ios::app);
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> amount_distribution(1, 100);
    uniform_int_distribution<> sleep_distribution(2, 5);

    for (int i = 0; i < transactionCount; ++i) {
        string senderPrivateKey = generatePrivateKey();
        string senderPublicKey = generatePublicKey(senderPrivateKey);
        string receiverPrivateKey = generatePrivateKey();
        string receiverPublicKey = generatePublicKey(receiverPrivateKey);
        int amount = amount_distribution(generator);

        if (transactions_file.is_open()) {
            transactions_file << senderPublicKey << "," << receiverPublicKey << "," << amount << endl;
        }

        this_thread::sleep_for(chrono::seconds(sleep_distribution(generator)));
    }

    transactions_file.close();
}

void printChain(Blockchain& blockchain)
{
    vector<Block> chain = blockchain.getChain();

    for (int i = 0; i < chain.size(); i++)
    {
        if (chain[i].index == 0)
            continue;
        cout << "Block " << chain[i].index << endl;
        cout << "Nonce " << chain[i].nonce << endl;
        cout << "Data: " << chain[i].data << endl;
        cout << "Previous Hash: " << chain[i].previousHash << endl;
        cout << "Hash: " << chain[i].currentHash << endl;
        cout << endl;
    }
}

int main() {
    Blockchain blockchain;
    vector<Block> chain = blockchain.getChain();

    resetResultsFile();

    string privateKey = generatePrivateKey();
    string publicKey = generatePublicKey(privateKey);

    MemoryPool memoryPool;
    MinerNode minerNode(publicKey, blockchain, memoryPool);

    thread transactionsThread(simulateIncomingTransactions, "transactions.txt", 200000);

    minerNode.readTransactionsFromFile();
    minerNode.startMining();

    transactionsThread.join();

    return 0;
}
