#include <iostream>
#include <cstring>
using namespace std;


//注意3*n的完美覆盖，重点是划分
//f(n) = 3f(n-2) + 2f(n-4) + 2f(n-6) + ...
//f(n) = 4f(n-2) - f(n-4)
int CountRecord[31];


int Count(int n){
    if(CountRecord[n] != 0)
        return CountRecord[n];
    if(n < 0) {
        return 0;
    } else{
        return 4 * Count(n-2) - Count(n-4);
    }
}

int main(){
    int n;
    cin >> n;
    memset(CountRecord, 0, sizeof(CountRecord));
    CountRecord[0] = 1;
    CountRecord[2] = 3;
    while(n != -1){
        cout << Count(n) << endl;
        cin >> n;
    }
    return 0;
}