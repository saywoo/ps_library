#include <bits/stdc++.h>
using namespace std;

// AAAAAAAAAABBBB 같은 문자열을 A10B4로 압축해주는 함수
// 작성: 2023/03/29

// 입력받은 문자열을 압축해주는 함수
void encode()
{
    // 입출력 파일 설정
    ifstream in("input.txt");
    ofstream out("loop_compresss_result.txt");

    string str = "", cache_str;

    // 줄바꿈도 입력을 받기 위해 EOF 사용
    while (getline(in, cache_str)) str = str + cache_str + '\n';

    // 입력받은 문자열의 정보 출력
    cout << "문자열 길이: " << str.length() << endl;

    char before_char;
    int loop_count = 0, len = str.length();
    string res = "";

    // 문자열을 하나씩 훑어보며 압축
    for (int i = 0; i < len; i++) {
        // 앞의 문자가 저장되어 있지 않다면 새로운 지정 문자 저장
        if (!before_char) {
            loop_count = 1;
            before_char = str[i];
        }
        // 앞의 문자와 지금의 문자가 다르다면 A10과 같은 형태로 저장
        else if (before_char != str[i]) {
            // 반복되는 문자를 추가
            res = res + before_char;
            
            // 반복되지 않으면 A의 형태로, 여러번 반복되면 A10의 형태로 저장
            cache_str = "";
            if (loop_count > 1) {
                // cache_str에 반복된 횟수를 문자열 형태로 저장
                for (int temp_int = loop_count; temp_int; temp_int /= 10) {
                    cache_str = (char)(temp_int % 10 + '0') + cache_str;
                }

                // 반복되는 횟수를 문자열에 저장
                res = res + cache_str;
            }

            // 새로운 지정 문자 저장
            loop_count = 1;
            before_char = str[i];
        }
        // 앞의 문자와 지금의 문자가 같다면 loop_count를 하나 더해주기
        else {
            loop_count++;
        }

        // 현재 상황을 출력
        if (i % 100000 == 0) cout << "압축 " << i << "자 완료." << endl;
    }

    // 모든 문자를 탐색하고 남은 글자를 저장
    // ------------
    // 반복되는 문자를 추가
    res = res + before_char;
            
    // 반복되지 않으면 A의 형태로, 여러번 반복되면 A10의 형태로 저장
    cache_str = "";
    if (loop_count > 1) {
        // cache_str에 반복된 횟수를 문자열 형태로 저장
        for (int temp_int = loop_count; temp_int; temp_int /= 10) {
            cache_str = (char)(loop_count % 10 + '0') + cache_str;
        }

        // 반복되는 횟수를 문자열에 저장
        res = res + cache_str;
    }
    // ------------

    out << res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    encode();

    return 0;
}
