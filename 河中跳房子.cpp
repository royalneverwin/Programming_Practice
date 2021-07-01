#include <iostream>
using namespace std;
int l, m, n;
int rock[50010];
bool ifDisRight(int dis){
    int moveCnt = 0;
    int prev = 0;
    int maxR = n; //别忘了初始化！因为下面的for循环可能不会给maxR赋值
    for(int i = n; i >= 1; i--){
        if(l - rock[i] < dis){
            moveCnt++;
            if(moveCnt > m)
                return false;
            maxR = i - 1;
        }
        else{
            break;
        }
    }
    for(int i = 1; i <= maxR; i++){
        if(rock[i] < prev + dis){
            moveCnt++;
            if(moveCnt > m)
                return false;
        }
        else{
            prev = rock[i];
        }
    }
    return true;
}
int main(){
    cin >> l >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> rock[i];
    }
    rock[n+1] = l;
    int maxDis = l;
    int minDis = 0;
    int middleDis;
    int ans;
    while(minDis <= maxDis){
        middleDis = (maxDis + minDis) / 2;
        bool flag = ifDisRight(middleDis);
        if(flag) {
            ans = middleDis;
            minDis = middleDis + 1;
        }
        else
            maxDis = middleDis - 1;
    }
    cout << ans << endl;
    return 0;

}