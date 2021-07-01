#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;


//贪心方法：如果powerMax 比 其余电池寿命之和都大，那么最长使用时间就是其余电池寿命之和
//如果powerMax 比 其余电池寿命之和小，那么最长使用时间是sum / 2（可以归纳证明得）
int n;
double power[1010];
int main(){
     while(cin >> n){
         double sum = 0;
         double maxP = 0;
         for(int i = 0; i < n; i++){
             cin >> power[i];
             maxP = max(maxP, power[i]);
             sum += power[i];
         }
         if(n == 2)
             cout << fixed << setprecision(1) << min(power[0], power[1]) << endl;
         else {
             if(2 * maxP > sum)
                 cout << fixed << setprecision(1) << sum - maxP << endl;
             else
                cout << fixed << setprecision(1) << sum / 2 << endl;
         }
     }
     return 0;
}