#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include "Tokenizer.h"
#include "Indexer.h"
#include "Ranker.h"

using namespace std;

int main() {
    ifstream file("data/Reviews.csv");
    if (!file.is_open()) return 1;

    Indexer indexer;
    Tokenizer::getNextReviewText(file); 
    
    unordered_map<int32_t, string> documentStore;
    int32_t docId = 1;
    
    cout << "[Engine] Indexing full dataset...\n";
    auto start = chrono::high_resolution_clock::now();

    while (true) {
        string raw = Tokenizer::getNextReviewText(file);
        if (raw.empty()) break; 
        if (docId <= 10000) documentStore[docId] = raw; 
        
        indexer.addDocument(docId, Tokenizer::cleanAndTokenize(raw));
        docId++;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "[Engine] Indexed " << (docId - 1) << " documents in " << duration.count() << " seconds.\n\n";

    Ranker ranker(indexer);
    
    string query;
    while (true) {
        cout << "\nEnter search query (or type 'exit' to quit): ";
        getline(cin, query);

        if (query == "exit") {
            cout << "Shutting down engine...\n";
            break;
        }

        if (query.empty()) continue;

        auto searchStart = chrono::high_resolution_clock::now();
        auto results = ranker.search(query, 5); // Increased to top 5 results
        auto searchEnd = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> searchTime = searchEnd - searchStart;

        cout << "\n=== SEARCH: '" << query << "' (" << searchTime.count() << " ms) ===\n";
        
        if (results.empty()) {
            cout << "No matching documents found.\n";
            continue;
        }

        for (const auto& result : results) {
            cout << "[Score: " << result.second << "] Doc ID: " << result.first << "\n";
            if (documentStore.find(result.first) != documentStore.end()) {
                cout << documentStore[result.first].substr(0, 100) << "...\n\n"; 
            }
        }
    }

    file.close();
    return 0;
}