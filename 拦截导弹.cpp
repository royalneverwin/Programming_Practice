#include <iostream>
#include <algorithm>
using namespace std;


//动态规划
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int k;
    int height[26];
    int maxHeighti[26];//表示最后一个拦截的导弹是第i个时拦截导弹的最大数量
    cin >> k;
    for(int i = 0; i < k; i++) {
        maxHeighti[i] = 1;
    }
    for(int i = 0; i < k ;i++){
        cin >> height[i];
    }
    maxHeighti[0] = 1;
    for(int i = 1; i < k; i++){
        for(int j = 0; j < i; j++){
            if(height[j] >= height[i]){//第i个导弹可以在第j个导弹后面拦截
                maxHeighti[i] = max(maxHeighti[i], maxHeighti[j] + 1);
            }
        }
    }
    sort(maxHeighti, maxHeighti + k, greater<int>());
    cout << maxHeighti[0] << endl;
    return 0;
}