#include "KeyGeneration.h"
#include <random>
#include <sstream>
#include <iomanip>

using namespace std;

string generatePrivateKey() {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, 255);

    stringstream ss;
    for (int i = 0; i < 32; ++i) {
        ss << hex << setw(2) << setfill('0') << distribution(generator);
    }

    return ss.str();
}

string generatePublicKey(const string& privateKey) {
    stringstream ss;
    for (size_t i = 0; i < privateKey.size(); ++i) {
        char c = privateKey[i];
        if (isdigit(c)) {
            ss << (9 - (c - '0'));
        }
        else {
            ss << char(((c - 'a' + 13) % 26) + 'a');
        }
    }
    return ss.str();
}
