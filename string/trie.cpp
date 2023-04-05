/*
trie 라이브러리
제작: 2023/04/05 saywoo

<사용법>
선언: Trie* root = new Trie;
추가: root->Insert(문자열.c_str());
찾기: root->Find(문자열.c_str());
삭제: root->Delete(문자열.c_str());
트라이 제거: delete root;
*/

#include <bits/stdc++.h>
using namespace std;

struct Trie {
    int child_num;
    bool finish;
    Trie* next[26];

    Trie() {
        child_num = 0;
        finish = false;
        for (int i = 0; i < 26; i++) next[i] = NULL;
    }
    ~Trie() {
        for (int i = 0; i < 26; i++) {
            if (next[i]) delete next[i];
        }
    }
    void Insert(const char* s) {
        child_num++;

        if (!*s) {
            this->finish = true;
            return;
        }

        int now = *s - 'A';
        if (!next[now]) next[now] = new Trie;
        next[now]->Insert(s + 1);
    }
    bool Find(const char* s) {
        if (!*s) return this->finish;

        int now = *s - 'A';
        if (!next[now]) return false;
        return next[now]->Find(s + 1);
    }
    bool Delete(const char* s) {
        this->child_num--;
        
        if (!*s) this->finish = false;
        else {
            int now = *s - 'A';
            if (!next[now]->Delete(s + 1)) {
                delete next[now];
                next[now] = nullptr;
            }
        }
        return this->child_num;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Trie* root = new Trie;

    string s = "ABCDEF";

    root->Insert(s.c_str());

    s = "ABC";

    root->Insert(s.c_str());

    cout << root->Find(s.c_str()) << endl;

    root->Delete(s.c_str());

    s = "ABCDEF";

    cout << root->Find(s.c_str()) << endl;

    s = "ABC";

    cout << root->Find(s.c_str()) << endl;
    
    return 0;
}