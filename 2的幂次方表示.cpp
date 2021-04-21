#include <iostream>
using namespace std;



void Find2Pow(int n){
    if(n == 1){
        cout << "2(0)";
        return;
    }
    if(n == 2){
        cout << "2";
        return;
    }
    if(n == 3){
        cout << "2+2(0)";
        return;
    }
    int maxPow = 0;
    int num = 1;
    while(n / num > 1){// = 1就可以退出了
        num *= 2;
        maxPow++;
    }
    cout << "2(";
    Find2Pow(maxPow);
    cout << ')';
    n = n % num;
    if(n != 0) {
        cout << "+";
        Find2Pow(n);
    }
}
int main(){
    int n;
    cin >> n;
    Find2Pow(n);
    return 0;
}