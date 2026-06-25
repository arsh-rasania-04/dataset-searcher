#ifndef RANKER_H
#define RANKER_H

#include "Indexer.h"
#include <string>
#include <vector>

using namespace std;

class Ranker {
private:
    const Indexer& indexer;

public:
    Ranker(const Indexer& idx);
    vector<pair<int32_t, double>> search(const string& query, int topN = 5);
};

#endif