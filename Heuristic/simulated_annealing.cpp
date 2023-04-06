/*

simulated annealing 구현 소스코드
제작: 2023/04/06

*/

#include <bits/stdc++.h>
using namespace std;

// 기본 변수 값 정하기
#define ORI_T 1
#define ORI_D 0.999999
#define ORI_K 4
#define ORI_LIM 0.00005

// t - 현재 온도, lim - 임계 온도, d = 온도 감률
double t = ORI_T, d = ORI_D, k = ORI_K, lim = ORI_LIM, local_pow = 0;

// random setting
mt19937_64 seed((unsigned)chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> rng(0, 1);
uniform_int_distribution<int> ran_num(1, 3);

// sa 변수들 초기화
void reset_sa()
{
    t = ORI_T, d = ORI_D, k = ORI_K, lim = ORI_LIM; local_pow = 0;
}

// 텍스트 input, output 설정
ifstream in("data.txt");
ofstream out("result.txt");

// 점수를 매기는 함수
int scoring()
{

}

// simulated annealing 함수
void simulated_annealing()
{
    int e1, e2;
    bool keep = false;

    while (t > lim) {
        // 기존의 상태의 점수를 측정
        if (!keep) e1 = scoring();
        keep = false;

        // 현재 상태를 백업


        // 상태를 변형


        // 상태를 변형한 후, e2로 점수 측정
        e2 = scoring();

        if (e2 < local_pow) {
            local_pow = 0;

            e1 = e2;
            keep = true;
        }
        else local_pow++;

        double p = exp((e1 - e2) / (t * k * log(local_pow)));

        if (p < rng(seed)) {
            // 복구

            keep = true;
        }
    }
}

int main()
{
    // 초기화

    // simulated annealing 실행
    simulated_annealing();

    return 0;
}
