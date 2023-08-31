#pragma once

#include <string>
#include "Blockchain.h"

using namespace std;

Transaction parseTransaction(const string& transaction_string);
string transactionToString(const Transaction& transaction);