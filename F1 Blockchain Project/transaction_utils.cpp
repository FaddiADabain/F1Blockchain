#include "transaction_utils.h"

using namespace std;

Transaction parseTransaction(const string& transaction_string) {
    stringstream ss(transaction_string);
    string sender, recipient;
    double amount;
    time_t timestamp;

    getline(ss, sender, ',');
    getline(ss, recipient, ',');
    ss >> amount;
    ss.ignore(1, ',');
    ss >> timestamp;

    Transaction transaction{ sender, recipient, amount, timestamp };
    return transaction;
}

string transactionToString(const Transaction& transaction) {
    stringstream ss;
    ss << transaction.sender << "," << transaction.recipient << "," << transaction.amount << "," << transaction.timestamp;
    return ss.str();
}