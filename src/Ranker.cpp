#include "Ranker.h"
#include "Tokenizer.h"
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

Ranker::Ranker(const Indexer& idx) : indexer(idx) {}

vector<pair<int32_t, double>> Ranker::search(const string& query, int topN) {
    vector<string> queryTokens = Tokenizer::cleanAndTokenize(query);
    unordered_map<int32_t, double> docScores;
    
    int32_t totalDocs = indexer.getTotalDocuments();
    double avgdl = indexer.getAverageDocumentLength();
    
    double k1 = 1.5;
    double b = 0.75;

    for (const string& token : queryTokens) {
        auto postingList = indexer.getPostingList(token);
        if (postingList.empty()) continue;

        double idf = log(((totalDocs - postingList.size() + 0.5) / (postingList.size() + 0.5)) + 1.0);

        for (const auto& posting : postingList) {
            int32_t docId = posting.first;
            int16_t tf = posting.second;
            double docLength = indexer.getDocumentLength(docId);
            
            double numerator = tf * (k1 + 1.0);
            double denominator = tf + k1 * (1.0 - b + b * (docLength / avgdl));
            
            docScores[docId] += idf * (numerator / denominator);
        }
    }

    vector<pair<int32_t, double>> results(docScores.begin(), docScores.end());
    
    sort(results.begin(), results.end(), 
        [](const pair<int32_t, double>& a, const pair<int32_t, double>& b) {
            return a.second > b.second;
        });

    if (results.size() > topN) results.resize(topN);

    return results;
}