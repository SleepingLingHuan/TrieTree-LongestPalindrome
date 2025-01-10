#include <iostream>
#include "TrieTree.h"
#include "suffixTree.h"

using namespace std;

int main() {
    TrieTree trie;
    trie.buildFromFile("wordset.txt");
    vector<pair<string, int>> top10 = trie.getTopKWords(10);

    cout << "����Ƶ����ߵ�ǰ10������:" << endl;
    for (auto& p : top10) cout << p.first << "��" << p.second << "��" << endl;

    string huiWenStr;
    cout << endl << "��������Ҫ����������Ӵ����ַ�����";
    cin >> huiWenStr;
    SuffixTree st;
    st.build(huiWenStr);
    string longestHuiWen = st.findLongestHuiWen(huiWenStr);
    cout << endl << "������Ӵ���" << longestHuiWen << endl;
    return 0;
}