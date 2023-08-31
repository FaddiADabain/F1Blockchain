#ifndef MINER_H
#define MINER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "Blockchain.h"

using namespace std;

string findHash(Block& block);
int leading(string hash);
void reHash(Block& block);
void creatBlock(string data, Blockchain& blockchain);
void mine(const Transaction& transaction, Blockchain& blockchain);
void resetResultsFile();

#endif
