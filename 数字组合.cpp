#include <iostream>
#include <cstring>
using namespace std;


int sum[21][1010]; //sum[i][j]表示从第1个数到第i个数和为j的组合个数
int num[21];


int Sum(int i, int j){
    if(j < 0){ //先判断是否j < 0，否则在下面可能会产生越界
        return 0;
    }
    if(sum[i][j] != -1){
        return sum[i][j];
    }
    if(j == 0){
        sum[i][j] = 1;
        return 1;
    }
    int s = 0;
    for(int tmp = 1; tmp <= i; tmp++){
        s += num[tmp];
    }
    if(s < j){
        sum[i][j] = 0;
        return 0;
    }
    sum[i][j] = Sum(i-1, j - num[i]) + Sum(i-1, j);
    return sum[i][j];
}


int main(){
    memset(sum, -1, sizeof(sum));
    int n, t;
    cin >> n >> t;
    for(int i = 1; i <= n; i++)
        cin >> num[i];
    cout << Sum(n, t) << endl;
    return 0;
}