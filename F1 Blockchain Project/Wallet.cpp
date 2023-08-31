#include "Wallet.h"
#include "KeyGeneration.h"
#include "transaction_utils.h"

Wallet::Wallet() {
    // Generate public and private keys
    privateKey = generatePrivateKey();
    publicKey = generatePublicKey(privateKey);
}

string Wallet::getPublicKey() const {
    return publicKey;
}

bool Wallet::createTransaction(const string& recipient, double amount, vector<Transaction>& transactions, const Blockchain& blockchain) {
    double currentBalance = getBalance(blockchain);

    if (amount <= 0) {
        cout << "Transaction amount should be greater than 0." << endl;
        return false;
    }

    if (currentBalance < amount) {
        cout << "Insufficient balance to create a transaction." << endl;
        return false;
    }

    Transaction newTransaction{ publicKey, recipient, amount, time(0) };
    transactions.push_back(newTransaction);
    return true;
}

double Wallet::getBalance(const Blockchain& blockchain) const {
    double balance = 0;
    const vector<Block>& chain = blockchain.getChain();

    for (const auto& block : chain) {
        Transaction transaction = parseTransaction(block.data);

        if (transaction.sender == "MINER" && transaction.recipient == publicKey) {
            balance += 10; // Assuming 10 coins as mining reward
        }
        else {
            if (transaction.sender == publicKey) {
                balance -= transaction.amount;
            }
            else if (transaction.recipient == publicKey) {
                balance += transaction.amount;
            }
        }
    }

    return balance;
}
