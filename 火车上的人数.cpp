#include <iostream>
using namespace std;


int main(){
    int a, n, m, x;
    cin >> a >> n >> m >> x;
    int tmp; //表示第二站上下车人数
    int total; //表示车上总人数
    int inBus, outBus;
    int prevIn;
    int preprevIn;
    for(tmp = 0;; tmp++){//注意这里tmp无上限，因为题目说了可以同一个人同一站先上车再下车
        total = a;
        preprevIn = a;
        prevIn = tmp;
        for(int i = 3; i <= n - 1; i++){
            inBus = preprevIn + prevIn;
            outBus = prevIn;
            preprevIn = prevIn;
            prevIn = inBus;
            total = total + inBus - outBus;
        }
        if(total == m){
            break;
        }
    }
    total = a;
    preprevIn = a;
    prevIn = tmp;
    for(int i = 3; i <= x; i++){
        inBus = preprevIn + prevIn;
        outBus = prevIn;
        preprevIn = prevIn;
        prevIn = inBus;
        total = total + inBus - outBus;
    }
    cout << total << endl;
    return 0;
}