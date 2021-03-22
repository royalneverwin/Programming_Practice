#include <iostream>
using namespace std;


//函数返回值为一个整数,该整数的左边i位是n的左边i位取反，其余位和n相同
int bitManipulation3(int n, int i) {
    return n ^ ((1 << 31) >> (i-1));
}

int main() {
    int t, n, i;
    cin >> t;
    while (t--) {
        cin >> n >> i;
        cout << bitManipulation3(n, i) << endl;
    }
    return 0;
}