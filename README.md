# High-Performance BM25 Search Engine in C++

This project is a high-performance C++ search engine that uses the Okapi BM25 ranking algorithm to instantly query massive text datasets. It features a custom, memory-safe CSV parser and a highly optimized inverted index capable of processing over half a million Amazon reviews in seconds. The result is a lightweight, terminal-based application that delivers lightning-fast, highly relevant search results with a minimal RAM footprint.

## Features

* **Okapi BM25 Ranking:** Replaces standard TF-IDF with enterprise-grade BM25 to prevent term frequency saturation and handle document length normalization.
* **Custom State-Machine CSV Parser:** Parses raw dataset character-by-character to perfectly handle edge cases like commas nested inside quotation marks without breaking column alignment.
* **Optimized Inverted Index:** Maps tokens to posting lists in $O(1)$ time, utilizing fixed-width integers (`int32_t`, `int16_t`) to compress memory footprint by over 60%.
* **Zero-Copy Architecture:** Passes data by constant references (`const &`) to strictly prevent RAM bloat and dangling pointers during the mathematical scoring phase.
* **Text Sanitization Pipeline:** Automatically strips HTML tags (e.g., `<br />`), normalizes punctuation, converts to lowercase, and filters mathematical stopwords.
