#include <iostream>
#include <cstring>
using namespace std;


long long Count[1000][1000]; //count[i][j]代表数i的分解个数，其中分解的最小数为j


long long Countf(int n, int x){
    if(Count[n][x] != 0)
        return Count[n][x];
    if(n == 0) {
        Count[n][x] = 1;
        return 1;
    }
    long long sum = 0;
    for(int i = x; i <= n/2; i++)
        sum += Countf(n-2*i, i);
    if(x <= n)
        sum++; //只有一个数n的分解
    Count[n][x] = sum;
    return sum;
}


int main(){
    memset(Count, 0, sizeof(Count));
    int n;
    cin >> n;
    while(n != 0){
        cout << n << ' ' << Countf(n, 1) << endl;
        cin >> n;
    }
    return 0;
}