#include <iostream>
#include <bitset>
using namespace std;


int main(){
    int a, b, i, j;
    cin >> a >> b >> i >> j;
    bitset<32> b1(a);
    bitset<32> b2(b);
    for(int idx = i; idx <= j; idx++){
        b2.flip(idx);
        b1[idx] = b2[idx];
    }
    cout << b1.to_ulong() << endl;
}