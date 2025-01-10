#include <iostream>
#include "TrieTree.h"
#include "suffixTree.h"

using namespace std;

int main() {
    TrieTree trie;
    trie.buildFromFile("wordset.txt");
    vector<pair<string, int>> top10 = trie.getTopKWords(10);

    cout << "出现频率最高的前10个单词:" << endl;
    for (auto& p : top10) cout << p.first << "：" << p.second << "次" << endl;

    string huiWenStr;
    cout << endl << "请输入需要查找最长回文子串的字符串：";
    cin >> huiWenStr;
    SuffixTree st;
    st.build(huiWenStr);
    string longestHuiWen = st.findLongestHuiWen(huiWenStr);
    cout << endl << "最长回文子串是" << longestHuiWen << endl;
    return 0;
}