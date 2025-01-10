#include "suffixTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

//根据单词表大小，预先分配长度和初始化
SuffixNode::SuffixNode(int Size) {
    children.resize(Size, nullptr);
    isLeaf = false;
}

SuffixTree::SuffixTree(int Size) : alphabetSize(Size) {
    root = new SuffixNode(alphabetSize); //构造后缀树的根节点
}

SuffixTree::~SuffixTree() {
    freeTree(root);
}

//递归释放后缀树中的所有节点
void SuffixTree::freeTree(SuffixNode* node) {
    if (!node) return;
    for (auto child : node->children) {
        if (child) {
            freeTree(child);
        }
    }
    delete node;
}

//通过对传入字符串的所有后缀进行插入，构建后缀树
void SuffixTree::build(const string& text) {
    for (size_t i = 0; i < text.size(); ++i) {
        insertSuffix(text.substr(i));
    }
}

//将单个后缀插入后缀树中，遍历后缀中的每个字符，按索引插到对应节点
void SuffixTree::insertSuffix(const string& suffix) {
    SuffixNode* current = root;
    for (char c : suffix) {
        int index = static_cast<int>(c);
        //若不存在对应节点，新建
        if (!current->children[index]) {
            current->children[index] = new SuffixNode(alphabetSize);
        }
        current = current->children[index];
    }
    current->isLeaf = true; //最后节点标记为叶子节点
}

//判断字符串是否为回文串
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

//查找最长回文子串
string SuffixTree::findLongestHuiWen(const string& text) {
    string longestHuiWen;
    int n = (int)text.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            //取子串[i,j]
            string substr = text.substr(i, j - i + 1);
            if (isHuiWen(substr) && (int)substr.size() > (int)longestHuiWen.size()) {
                longestHuiWen = substr;
            }
        }
    }
    return longestHuiWen;
}