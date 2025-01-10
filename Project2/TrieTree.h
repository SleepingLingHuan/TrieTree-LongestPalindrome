#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    int endCount;
    TrieNode();
    ~TrieNode();
};

class TrieTree {
public:
    TrieNode* root;
    TrieTree();
    ~TrieTree();
    void countWords(TrieNode* node, string current, vector<pair<string, int>>& result);
    void insert(const string& word);
    bool search(const string& word);
    vector<pair<string, int>> getTopKWords(int k);
    void buildFromFile(const string& filename);
};