#include <iostream>
using namespace std;


const int MAXLEN = (1 << 31) - 1;


int main(){
    int n;
    cin >> n;
    int begin = n + 1;
    int Cnt;
    while(1) {
        int flag = 1;
        Cnt = begin;
        for (int i = 2; i <= n; i++) {
            if(Cnt % (n - 1) != 0){
                flag = 0;
                break;
            }
            Cnt = Cnt / (n - 1) * n + 1; //注意这里先除后乘，防止溢出现象！！！
        }
        if(flag){
            break;
        }
        begin += n;
    }
    cout << Cnt << endl;
    return 0;
}