#include <iostream>
using namespace std;

int main(){
    int p, e, i, d;
    int day;
    int Case = 1;
    while((cin >> p >> e >> i >> d) && (p >= 0)) {
        for(day = d+1; (day-p) % 23; day++);//先找体力高峰
        for(;(day - e) % 28; day += 23);//再找体力和情商双高峰，day每次+23，减少枚举次数
        for(;(day - i) % 33; day += 23*28);//最后找三高峰，day每次+23*28，减少枚举次数
        cout << "Case " << Case << ": the next triple peak occurs in " << day - d << " days." << endl;
        Case++;
    }
    return 0;
}
