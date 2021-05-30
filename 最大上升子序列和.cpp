#include <iostream>
#include <cstring>
using namespace std;


int sum[1010]; //sum[i]代表上升子序列最后一个数为第i个时的最大值
int num[1010];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> num[i];
        sum[i] = num[i];
    }
    int Max = 0;
    for(int i = 0; i < n; i++){
        int tmpS = sum[i];
        for(int j = 0; j < i; j++){
            if(num[j] < num[i]){
                if(sum[j] + num[i] > tmpS)
                    tmpS = sum[j] + num[i];
            }
        }
        sum[i] = tmpS;
        Max = max(Max, sum[i]);
    }
    cout << Max << endl;
    return 0;
}