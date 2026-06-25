#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;

class Indexer {
private:
    unordered_map<string, vector<pair<int32_t, int16_t>>> invertedIndex;
    unordered_map<int32_t, int32_t> docLengths;
    int32_t totalDocuments = 0;
    int64_t totalTokens = 0;

public:
    void addDocument(int32_t docId, const vector<string>& tokens);
    void printStatsForTerm(const string& term);
    int32_t getTotalDocuments() const { return totalDocuments; }
    double getAverageDocumentLength() const;
    int32_t getDocumentLength(int32_t docId) const;
    const vector<pair<int32_t, int16_t>>& getPostingList(const string& term) const;
};

#endif