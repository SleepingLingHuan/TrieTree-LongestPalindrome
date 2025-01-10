#pragma once
#include <string>
#include <vector>
using namespace std;

class SuffixNode {
public:
    vector<SuffixNode*> children;
    bool isLeaf;
    SuffixNode(int alphabetSize = 128);
};

class SuffixTree {
public:
    SuffixNode* root;
    int alphabetSize;
    SuffixTree(int alphSize = 128);
    ~SuffixTree();
    void build(const string& text);
    string findLongestHuiWen(const string& text);
    void freeTree(SuffixNode* node);
    void insertSuffix(const string& suffix);
    bool isHuiWen(const string& s);
};