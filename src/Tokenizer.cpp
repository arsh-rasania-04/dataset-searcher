#include "Tokenizer.h"
#include <unordered_set>
#include <cctype>
#include <sstream>

using namespace std;

static const unordered_set<string> STOPWORDS = {
    "a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "as", "at",
    "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", "can", "could", "did",
    "do", "does", "doing", "down", "during", "each", "few", "for", "from", "further", "had", "has", "have",
    "having", "he", "her", "here", "hers", "herself", "him", "himself", "his", "how", "i", "if", "in", "into",
    "is", "it", "its", "itself", "just", "me", "more", "most", "my", "myself", "no", "nor", "not", "now", "of",
    "off", "on", "once", "only", "or", "other", "our", "ours", "ourselves", "out", "over", "own", "s", "same",
    "she", "should", "so", "some", "such", "t", "than", "that", "the", "their", "theirs", "them", "themselves",
    "then", "there", "these", "they", "this", "those", "through", "to", "too", "under", "until", "up", "very",
    "was", "we", "were", "what", "when", "where", "which", "while", "who", "whom", "why", "will", "with", "you",
    "your", "yours", "yourself", "yourselves", "br" 
};

string Tokenizer::getNextReviewText(ifstream& file) {
    string reviewText;
    int currentColumn = 0;
    bool insideQuotes = false;
    char c;
    
    while (file.get(c)) {
        if (c == '"') {
            insideQuotes = !insideQuotes;
            continue;
        } 
        if (c == ',' && !insideQuotes) {
            currentColumn++;
            continue;
        } 
        if (c == '\n' && !insideQuotes) {
            return reviewText; 
        }
        if (c == '\r' && !insideQuotes) {
            if (file.peek() == '\n') file.get();
            return reviewText;
        }
        if (currentColumn == 9) {
            reviewText += c;
        }
    }
    return reviewText;
}

vector<string> Tokenizer::cleanAndTokenize(const string& rawText) {
    string cleanedText = "";
    bool insideHtmlTag = false;

    for (char c : rawText) {
        if (c == '<') { insideHtmlTag = true; continue; }
        if (c == '>') { insideHtmlTag = false; continue; }
        if (insideHtmlTag) continue;

        if (isalnum(c)) {
            cleanedText += tolower(c);
        } else if (isspace(c) || c == '\n') {
            cleanedText += ' '; 
        }
    }

    vector<string> tokens;
    stringstream ss(cleanedText);
    string word;

    while (ss >> word) {
        if (STOPWORDS.find(word) == STOPWORDS.end()) {
            tokens.push_back(word);
        }
    }
    return tokens;
}