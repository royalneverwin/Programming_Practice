#include <iostream>
using namespace std;


int other2dec(int other, int num){//把other进制数转化成10进制
    int bit[10];
    int index = 0;
    while(num != 0){
        bit[index] = num % 10;
        num = num / 10;
        if(bit[index] >= other) //这里要判断输入的数是否符合进制，数的每一位一定比进制数要小
            return -1;
        index++;
    }
    int sum = 0;
    for(int i = index - 1; i >= 0; i--){
        sum = sum * other + bit[i];
    }
    return sum;
}


int main(){
    int p, q, r;
    cin >> p >> q >> r;
    for(int i = 2; i <= 16; i++) {
        int pp = other2dec(i, p);
        int qq = other2dec(i, q);
        int rr =  other2dec(i, r);
        if (pp != -1 && qq != -1 && rr != -1 && pp * qq == rr) {
            cout << i << endl;
            return 0;
        }
    }
    cout << 0 << endl;
    return 0;
}