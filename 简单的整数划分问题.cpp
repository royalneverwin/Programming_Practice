#include <iostream>
using namespace std;





int Calculate(int n, int m, int min){//将n个数字分成m份, 其中最小的份数大小为min的种数
    if(m == 1){
        return 1;
    }
    int sum = 0;
    for(int i = min; i <=  n/m; i++){
        sum += Calculate(n - i, m - 1, i);
    }
    return sum;
}


int main(){
    int n;
    int sum;
    while(cin >> n){
        sum = 0;
        for(int i = 1; i <= n; i++){
            sum += Calculate(n, i, 1);
        }
        cout << sum << endl;
    }
    return 0;
}