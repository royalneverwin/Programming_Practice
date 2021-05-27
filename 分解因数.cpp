#include <iostream>
using namespace std;


int Count(int num, int x){//表示将num分解成最小值为x的因子乘积的种数
    if(num < x){
        return 0;
    }
    if(num == x){
        return 1;
    }
    int sum = 0;
    for(int i = x; i < num; i++){
        if(num % i == 0){
            sum += Count(num / i, i);
        }
    }
    sum += 1; //分解成自己本身的乘积
    return sum;
}


int main(){
    int n;
    cin >> n;
    int num;
    while(n--){
        cin >> num;
        cout << Count(num, 2) << endl;
    }
    return 0;
}