#ifndef KEYGENERATION_H
#define KEYGENERATION_H

#include <string>

using namespace std;

string generatePrivateKey();
string generatePublicKey(const string& privateKey);

#endif
