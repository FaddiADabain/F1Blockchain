#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include "Blockchain.h"

using namespace std;

class Wallet {
private:
    string publicKey;
    string privateKey;

public:
    Wallet();
    string getPublicKey() const;
    bool createTransaction(const string& recipient, double amount, vector<Transaction>& transactions, const Blockchain& blockchain);
    double getBalance(const Blockchain& blockchain) const;
};

#endif
