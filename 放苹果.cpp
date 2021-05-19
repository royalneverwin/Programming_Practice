#include <iostream>
using namespace std;


int f(int i, int k){//设i个苹果放在k个盘子里放法总数
    if(k > i){
        return f(i, i);
    }
    if(i == 0){//先判断苹果是否为0，再判断盘子是否为0
        return 1;
    }
    if(k == 0){
        return 0;
    }
    return f(i, k-1) + f(i-k, k);
}


int main(){
    int t, m, n;
    cin >> t;
    while(t--){
        cin >> m >> n;
        cout << f(m, n) << endl;
    }
    return 0;
}