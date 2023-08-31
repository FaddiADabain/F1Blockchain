#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "sha256.h"
#include "Blockchain.h"
#include "Miner.h"
#include "transaction_utils.h"

using namespace std;

void resetResultsFile() {
    ofstream results_file("results.txt", ios::trunc);
    results_file.close();
}

string findHash(Block& block)
{
    SHA256 sha256;
    time_t timestamp = time(nullptr);
    string toHash = to_string(block.index) + to_string(block.nonce) + to_string(timestamp) + block.data + block.previousHash;
    return sha256(toHash);
}

int leading(string hash)
{
    if (hash.rfind("00000", 0) == 0)
        return 1;
    else
        return 0;
}

void reHash(Block& block)
{
    while (leading(block.currentHash) < 1)
    {
        block.nonce += 1;
        block.currentHash = findHash(block);
    }
}

void creatBlock(string data, Blockchain& blockchain)
{
    vector<Block> chain = blockchain.getChain();
    Block temp(chain.size(), 0, data, chain.back().currentHash, "0");
    temp.currentHash = findHash(temp);
    reHash(temp);
    blockchain.addBlock(Block(temp.index, temp.nonce, temp.data, temp.previousHash, temp.currentHash));
}

void mine(const Transaction& transaction, Blockchain& blockchain) {
    // Initialize variables
    int index = 0;
    int nonce = 0;
    time_t timestamp = time(nullptr);
    string previous_hash = "";
    string current_hash = "";
    bool block_found = false;

    // Convert transaction object to string
    string transactionData = transactionToString(transaction);

    // Mine for block
    creatBlock(transactionToString(transaction), blockchain);
}
