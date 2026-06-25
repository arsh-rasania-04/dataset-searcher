#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Tokenizer {
public:
    static string getNextReviewText(ifstream& file);
    static vector<string> cleanAndTokenize(const string& rawText);
};

#endif