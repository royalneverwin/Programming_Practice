#include <iostream>
using namespace std;


bool is_Prime[100010];


bool if_Prime(int n){
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}


void Prime(){
    is_Prime[1] = false;
    for(int i = 2; i <= 100000; i++){
        is_Prime[i] = if_Prime(i);
    }
}


int Rotate(int n){
    int sum = 0;
    while(n > 0){
        sum = sum * 10 + n % 10;
        n /= 10;
    }
    return sum;
}


int main(){
    int m, n;
    cin >> m >> n;
    int flag = 0;
    Prime();
    for(int i = m; i <= n; i++){
        if(is_Prime[i] && is_Prime[Rotate(i)]) {
            if (flag) {
                cout << ',';
            }
            flag = 1;
            cout << i;
        }
    }
    if(!flag){
        cout << "No" << endl;
    }
    return 0;
}