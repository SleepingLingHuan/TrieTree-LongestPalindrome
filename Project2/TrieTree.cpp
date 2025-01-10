#include "TrieTree.h"
#include <fstream>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

TrieNode::TrieNode() : endCount(0) {}

//�����ݹ��ͷ��ӽڵ�
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
        //�����Ӧ�ӽڵ㲻���ڣ��򴴽���TrieNode
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->endCount++; //�����һ���ڵ㴦�ۼӼ���
}

bool TrieTree::search(const string& word) {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) return false;  //��;�Ͽ���������
        current = current->children[c];
    }
    return (current->endCount > 0); //������������
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

//����Ƶ����ߵ�k������
vector<pair<string, int>> TrieTree::getTopKWords(int k) {
    vector<pair<string, int>> allWords;
    countWords(root, "", allWords);
    sort(allWords.begin(), allWords.end(), [](auto& a, auto& b) { return a.second > b.second; }); //����Ƶ�ν�������
    if ((int)allWords.size() > k) allWords.resize(k);
    return allWords;
}

//���ļ������ж�ȡ���ʣ�����Trie��
void TrieTree::buildFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "�ļ���ʧ�ܣ�" << filename << endl;
        return;
    }
    string word;
    while (fin >> word) insert(word);
    fin.close();
}