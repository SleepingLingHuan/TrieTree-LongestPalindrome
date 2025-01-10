#include "TrieTree.h"
#include <fstream>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

TrieNode::TrieNode() : endCount(0) {}

//析构递归释放子节点
TrieNode::~TrieNode() {
    for (auto& kv : children) {
        delete kv.second;
    }
    children.clear();
}

TrieTree::TrieTree() {
    root = new TrieNode();
}

TrieTree::~TrieTree() {
    delete root;
}

void TrieTree::insert(const string& word) {
    TrieNode* current = root;
    for (char c : word) {
        //如果对应子节点不存在，则创建新TrieNode
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->endCount++; //在最后一个节点处累加计数
}

bool TrieTree::search(const string& word) {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) return false;  //中途断开，不存在
        current = current->children[c];
    }
    return (current->endCount > 0); //检查计数大于零
}

void TrieTree::countWords(TrieNode* node, string current, vector<pair<string, int>>& result) {

    if (node->endCount > 0) {
        result.push_back({ current, node->endCount });
    }
    for (auto& kv : node->children) {
        char c = kv.first;
        TrieNode* child = kv.second;
        countWords(child, current + c, result);
    }
}

//返回频次最高的k个单词
vector<pair<string, int>> TrieTree::getTopKWords(int k) {
    vector<pair<string, int>> allWords;
    countWords(root, "", allWords);
    sort(allWords.begin(), allWords.end(), [](auto& a, auto& b) { return a.second > b.second; }); //单词频次降序排序
    if ((int)allWords.size() > k) allWords.resize(k);
    return allWords;
}

//从文件中逐行读取单词，插入Trie树
void TrieTree::buildFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "文件打开失败：" << filename << endl;
        return;
    }
    string word;
    while (fin >> word) insert(word);
    fin.close();
}