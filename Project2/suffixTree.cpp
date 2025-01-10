#include "suffixTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

//���ݵ��ʱ��С��Ԥ�ȷ��䳤�Ⱥͳ�ʼ��
SuffixNode::SuffixNode(int Size) {
    children.resize(Size, nullptr);
    isLeaf = false;
}

SuffixTree::SuffixTree(int Size) : alphabetSize(Size) {
    root = new SuffixNode(alphabetSize); //�����׺���ĸ��ڵ�
}

SuffixTree::~SuffixTree() {
    freeTree(root);
}

//�ݹ��ͷź�׺���е����нڵ�
void SuffixTree::freeTree(SuffixNode* node) {
    if (!node) return;
    for (auto child : node->children) {
        if (child) {
            freeTree(child);
        }
    }
    delete node;
}

//ͨ���Դ����ַ��������к�׺���в��룬������׺��
void SuffixTree::build(const string& text) {
    for (size_t i = 0; i < text.size(); ++i) {
        insertSuffix(text.substr(i));
    }
}

//��������׺�����׺���У�������׺�е�ÿ���ַ����������嵽��Ӧ�ڵ�
void SuffixTree::insertSuffix(const string& suffix) {
    SuffixNode* current = root;
    for (char c : suffix) {
        int index = static_cast<int>(c);
        //�������ڶ�Ӧ�ڵ㣬�½�
        if (!current->children[index]) {
            current->children[index] = new SuffixNode(alphabetSize);
        }
        current = current->children[index];
    }
    current->isLeaf = true; //���ڵ���ΪҶ�ӽڵ�
}

//�ж��ַ����Ƿ�Ϊ���Ĵ�
bool SuffixTree::isHuiWen(const string& s) {
    int left = 0;
    int right = (int)s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

//����������Ӵ�
string SuffixTree::findLongestHuiWen(const string& text) {
    string longestHuiWen;
    int n = (int)text.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            //ȡ�Ӵ�[i,j]
            string substr = text.substr(i, j - i + 1);
            if (isHuiWen(substr) && (int)substr.size() > (int)longestHuiWen.size()) {
                longestHuiWen = substr;
            }
        }
    }
    return longestHuiWen;
}