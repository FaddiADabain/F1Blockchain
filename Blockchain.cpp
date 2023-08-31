#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "sha256.h"

using namespace std;

struct Block
{
    int index;
    size_t nonce;
    time_t timestamp;
    string data;
    string previousHash;
    string currentHash;

    Block(int index, const size_t& nonce, const string& data, const string& previousHash, const string& currentHash)
        : index(index), nonce(nonce), timestamp(time(NULL)), data(data), previousHash(previousHash), currentHash(currentHash)
    {

    }
};

class Blockchain
{
private:
    vector<Block> chain;

public:
    Blockchain()
    {
        // Create the genesis block
        Block genesis(0, 0, "Genesis Block", "", "Genesis Block");
        chain.push_back(genesis);
    }

    void addBlock(const Block& newBlock)
    {
        chain.push_back(newBlock);
    }

    vector<Block>& getChain()
    {
        return chain;
    }
};
