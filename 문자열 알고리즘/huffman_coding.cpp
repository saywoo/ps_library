#include <bits/stdc++.h>
using namespace std;

// 허프만 트리 구현체
// 출처: https://lipcoder.tistory.com/187
// todo -> 직접 구현한 구현체로 교체하기
// -------------------------------------------------------------------

// 노드 정보
struct Node
{
	char character;
	int frequency;
	Node *left, *right;
};

// 우선순위 큐 정렬을 위한 구조체
// 빈도수를 기준으로 최소힙으로 정렬한다.
struct cmp
{
	bool operator()(Node* A, Node* B)
	{
		return A->frequency > B->frequency;
	}
};

class HuffmanTree
{
public:
	~HuffmanTree()
	{
		// 동적할당 받은 노드들을 지운다.
		ReleaseTree(root);
		root = nullptr;
		um.clear();
		info.clear();
		while (!pq.empty()) pq.pop();
	}
public:
	const unordered_map<char, string>& GetInfo() 
	{ 
		// 허프만 트리로 얻은 알파벳 별 이진수 정보를 가져온다.
		return info; 
	}
public:
	// 압축할 문자열 정보를 바탕으로 허프만 트리를 만들어
	// 이진수 정보들을 만든다.
	void Create(const string& str)
	{
		// 해쉬 테이블을 이용해 빈도수를 기록
		for (const auto iter : str) ++um[iter];	
		for (const auto iter : um)
		{
			// 해쉬 테이블에서 하나씩 꺼내 
			// 정보를 노드에 저장 후
			// 우선순위 큐에 집어 넣는다.
			Node* newNode = new Node;
			newNode->left = nullptr;
			newNode->right = nullptr;
			newNode->character = iter.first;
			newNode->frequency = iter.second;
			pq.push(newNode);
		}
		// 우선순위 큐 정보를 바탕으로 트리를 만든다.
		MakeTree();
		// 트리를 순회하면서 이진수 정보를 입력받는다.
		string tmp = "";
		FindTree(root, tmp);
	}
private:
	void MakeTree()
	{
		// 우선 순위 큐를 이용해 빈도수가 작은 순으로 
		// 2개씩 꺼내 두 노드를 담는 노드를 만들어
		// 두 노드의 빈도수를 합치고 큐에 다시 집어 넣는다.
		int limit = pq.size() - 1;
		for (int i = 0; i < limit; ++i)
		{
			Node* newNode = new Node;
			newNode->character = 0;
			newNode->right = pq.top(); pq.pop();
			newNode->left = pq.top(); pq.pop();
			newNode->frequency = newNode->right->frequency + newNode->left->frequency;
			pq.push(newNode);
		}

		// 이 작업을 마치면 우선순위 큐에는 한가지 원소만 남는다.
		// 그것이 허프만 트리의 Root 노드가 된다.
		root = pq.top();
	}
	void FindTree(Node* p, string str)
	{
		if (p == nullptr) return;
		// 왼쪽은 0, 오른쪽은 1
		// 순회하면서 정보를 더해간다.
		FindTree(p->left, str + '0');
		FindTree(p->right, str + '1');
		// 알파벳 정보를 가진 노드를 만날때까지 순회한다.
		if (p->character != 0)
		{
			info[p->character] = str;
		}
	}
	void ReleaseTree(Node* p)
	{
		// 후위 순화를 하면서 동적할당 했던 노드들을
		// 할당 해제 시켜준다.
		if (p == nullptr) return;
		ReleaseTree(p->left);
		ReleaseTree(p->right);
		delete p;
		p = nullptr;
	}
private:
	Node* root = nullptr;
	unordered_map<char, int> um;
	unordered_map<char, string> info;
	priority_queue<Node*, vector<Node*>, cmp> pq;
};

// -------------------------------------------------------------------


// 허프만 코딩으로 문자열을 압축하는 함수
void encode()
{
    // 입출력 파일 지정
	ifstream in("input.txt");
    ofstream out_str("output_str.txt");
	ofstream out_code("output_code.txt");

    // 파일에서 문자열을 입력받기
    string str = "", temp_str;
    while (in >> temp_str) str = str + "\n" + temp_str;

    // 허프만 코드 생성
	HuffmanTree t;
	t.Create(str);
	unordered_map<char, string> info = t.GetInfo();

    // iter.first = 아스키코드
    // iter.second = 허프만 코드
	for (const auto iter : info) {
        int pos = 1;
        for (int i = 0; i < iter.second.length(); i++) {
            pos *= 2;
            if (iter.second[i] == '1') pos++;
        }

        // 허프만 코드값을 파일에 저장
        out_code << "huffman_code[" << pos << "]=" << (int)iter.first << ";";
	}

	// 압축 결과물인 이진수를 (이진수 62바이트) -> (char형 글자 9자)로 변환
    string res = ""; int cnt = 0;
    string memo = ""; int ans = 0;
	for (const auto iter : str) {
        string temp = info[iter];
        ans += temp.length();

        for (int i = 0; i < temp.length(); i++) {
            memo = memo + temp[i];
            cnt++;

            if (cnt == 62) {
                unsigned long long int t = 0, pw = 1;
                for (int j = 0; j < 62; j++, pw *= 2) {
                    if (memo[j] == '1') t += pw;
                }

                for (int j = 0; j < 9; t /= 119, j++) {
                    int ch = t % 119;
                    if (ch >= 18) ch += 9;
                    else if (ch >= 6) ch += 8;
                    else if (ch >= 5) ch += 5;
                    else ch += 1;

                    res = res + (char)ch;
                }

                memo = "";
                cnt = 0;
            }
        }
	}
    if (cnt) {
        for (; cnt < 62; cnt++) { memo = memo + '0'; ans++; }
        unsigned long long int t = 0, pw = 1;
        for (int j = 0; j < 62; j++, pw *= 2) {
            if (memo[j] == '1') t += pw;
        }

        for (int j = 0; j < 9; t /= 119, j++) {
            int ch = t % 119;
            if (ch >= 18) ch += 9;
            else if (ch >= 6) ch += 8;
            else if (ch >= 5) ch += 5;
            else ch += 1;

            res = res + (char)ch;
        }
    }

    // 압축된 결과 문자열을 파일에 저장
    out_str << res;
}

// 허프만 코딩으로 압축된 문자열을 복원하는 함수
string decode(string input_string)
{
    // pos = 허프만 코드 트리를 탐색할 때의 위치
    // huffman_code 허프만 코드의 각 노드가 리프 노드라면 해당하는 문자를 저장해놓는 배열
    int pos = 1, huffman_code[1000001];

    // 여기에 허프만 코드의 각 노드에 해당하는 문자를 저장

    // -----------------------------------------------

    // ret = 복원한 문자열을 저장
    string ret = "";

    for (int i = 0; i < input_string.length(); i += 9) {
        // bt = 9개의 char글자에서 2진수 62자로 변환한 것을 저장
        unsigned long long int bt = 0, pw = 1;

        for (int j = 8; j >= 0; j--) {
            int ch = input_string[i+j];
            
            // 0~127의 아스키코드에서 0~118의 119개의 수 중 하나로 변환
            ch = ch < 6 ? ch - 1 : ch < 11 ? ch - 5 : ch < 26 ? ch - 8 : ch - 9;

            bt = bt * 119 + ch;
        }

        // 2진수 62자가 저장된 bt를 보고 순서대로 허프만 코드 트리를 탐색하며 글자를 복원
        for (int j = 0; j < 62; j++, pw *= 2) {
            pos *= 2;
            if (bt & pw) pos++;

            // 허프만 코드 트리의 리프노드에 도달했으므로 해당하는 글자로 복원
            if (huffman_code[pos]) {
                ret = ret + (char)huffman_code[pos];
                pos = 1;
            }
        }
    }

    // 결과값을 반환
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    return 0;
}