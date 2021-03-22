#include <iostream>
using namespace std;


//n级台阶的走法 = n-1级台阶的走法 + n-2级台阶的走法
int f(int n){
    if(n == 1) return 1;
    else if(n == 2) return 2;
    return f(n-1) + f(n-2);
}


const int MAX = 10000;
int Ways[MAX];


int main(){
    int T;
    int n;
    cin >> T;
    Ways[1] = 1;
    Ways[2] = 2;
    for(int i = 0; i < T; i++){//动态规划做法
        cin >> n;
        for(int j = 3; j <= n; j++){
            Ways[j] = Ways[j-1] + Ways[j-2];
        }
        cout << Ways[n] << endl;
    }
    return 0;
}