#include "Indexer.h"
#include <iostream>

using namespace std;

void Indexer::addDocument(int32_t docId, const vector<string>& tokens) {
    totalDocuments++;
    int32_t length = tokens.size();
    docLengths[docId] = length;
    totalTokens += length;
    
    unordered_map<string, int16_t> localTermCount;
    for (const string& token : tokens) {
        localTermCount[token]++;
    }

    for (const auto& pair : localTermCount) {
        invertedIndex[pair.first].push_back({docId, pair.second});
    }
}

void Indexer::printStatsForTerm(const string& term) {
    auto it = invertedIndex.find(term);
    
    if (it == invertedIndex.end()) {
        cout << term << " not found\n";
        return;
    }

    const auto& postingList = it->second;
    cout << term << " found in " << postingList.size() << "\n";
    
    int displayCount = min(5, (int)postingList.size());
    for (int i = 0; i < displayCount; i++) {
        cout << postingList[i].first << " " << postingList[i].second << "\n";
    }
}

double Indexer::getAverageDocumentLength() const {
    if (totalDocuments == 0) return 0.0;
    return static_cast<double>(totalTokens) / totalDocuments;
}

int32_t Indexer::getDocumentLength(int32_t docId) const {
    auto it = docLengths.find(docId);
    return (it != docLengths.end()) ? it->second : 0;
}

const vector<pair<int32_t, int16_t>>& Indexer::getPostingList(const string& term) const {
    static const vector<pair<int32_t, int16_t>> emptyList;
    auto it = invertedIndex.find(term);
    return (it != invertedIndex.end()) ? it->second : emptyList;
}