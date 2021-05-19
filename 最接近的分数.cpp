#include <iostream>
using namespace std;


int gcd(int m, int n){
    return m % n == 0? n: gcd(n, m % n);
}
int main() {
    int n, a, b;
    cin >> n >> a >> b;
    int maxm, maxn;
    double max = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * b < i * a; j++) {
            if (max < float(j) / i) {
                maxm = j;
                maxn = i;
                max = float(j) / i;
            }
        }
    }
    int tmp = gcd(maxm, maxn);
    maxm /= tmp;
    maxn /= tmp;
    cout << maxm << ' ' << maxn << endl;
    return 0;
}