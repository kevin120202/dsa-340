#include "wordcount.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>

WordCount::WordCount(int sz) : tableSize(sz) {
    hashTable.resize(sz); // Resize the vector to the hash table size
}

int WordCount::hash(string s) {
    return hashFunction(s) % tableSize; // Apply hash function and modulus
}

int WordCount::count(string word) {
    int index = hash(word); // Compute hash index
    for (const auto& pair : hashTable[index]) {
        if (pair.first == word) {
            return pair.second; // Return count if word exists
        }
    }
    return 0; // Word not found
}

void WordCount::add(string word) {
    int index = hash(word); // Compute hash index
    auto& list = hashTable[index];

    // Find if the word already exists
    auto it = std::find_if(list.begin(), list.end(),
        [&word](const std::pair<string, int>& pair) {
            return pair.first == word;
        });

    if (it != list.end()) {
        it->second++; // Increment count if word exists
    } else {
        list.emplace_back(word, 1); // Add new word with count 1
    }
}

void printFileWordCount(string filename, int tableSize) {
    WordCount wc(tableSize);
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    string word;
    while (file >> word) {
        // Remove punctuation
        word.erase(
            std::remove_if(word.begin(), word.end(), ::ispunct),
            word.end()
        );

        // Convert to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        wc.add(word); // Add word to WordCount
    }

    wc.print(); // Print the word count
}

void WordCount::print() {
    std::vector<std::pair<string, int>> words;
    for (auto entry: hashTable)
        for (auto pair: entry)
            words.push_back(pair);
    sort(words.begin(), words.end());
    for (auto pair: words)
        std::cout << pair.first << ": " << pair.second << std::endl;
}