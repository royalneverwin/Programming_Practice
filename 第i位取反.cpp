
#include <iostream>
using namespace std;


//函数返回值为一个整数,该整数的第i位是n的第i位取反，其余位和n相同
int bitManipulation2(int n, int i) {
    return n ^ (1 << i);
}

int main() {
    int t, n, i;
    cin >> t;
    while (t--) {
        cin >> n >> i;
        cout << bitManipulation2(n, i) << endl;
    }
    return 0;
}