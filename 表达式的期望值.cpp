#include <iostream>
#include <iomanip>
using namespace std;
//因为位运算只会和当前位有关，而且数字一共不会超过20位，所以我们可以针对每一位进行位运算并计算出期望值
//时间复杂度为20 * n
int n;
int A[202];
char O[201];
double P[201];
inline double f(double tmp, char O, bool result){ //用来求得增加一个数字后的运算结果
    switch(O){
        case '&':
            return result ? tmp: 0;
        case '|':
            return result ? 1 : tmp;
        case '^':
            return result ? 1 - tmp : tmp;
        default:
            return 0;
    }
}
int main(){
    int cnt = 0;
    while(cin >> n) {
        cnt++;
        double ans = 0;
        for (int i = 0; i <= n; i++)
            cin >> A[i];
        for (int i = 1; i <= n; i++)
            cin >> O[i];
        for (int i = 1; i <= n; i++)
            cin >> P[i];
        for(int i = 0; i <= 20; i++) {
            double tmp = (A[0] >> i) & 1; //tmp表示该位为1的概率
            for (int j = 1; j <= n; j++) {
                tmp = tmp * P[j] + f(tmp, O[j], (A[j] >> i) & 1) * (1 - P[j]);
            }
            ans += (1 << i) * tmp;
        }
        cout << "Case " << cnt << ':' << endl;
        cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}