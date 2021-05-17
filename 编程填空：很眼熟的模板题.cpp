#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
// 在此处补充你的代码
template <class T, int size>
class A{
public:
    T *vec;
    A(const T *other){
        vec = new T[size];
        for(int i = 0; i < size; i++){
            vec[i] = other[i];
        }
    }
    template <class T2>
    T2 sum(int begin, int end, T2 op(T)){
        T2 _sum = op(vec[begin]);
        for(int i = begin + 1; i <= end; i++){
            _sum += op(vec[i]);
        }
        return _sum;
    }
};
string int2string(int x) { return to_string(x); }
int int2squareint(int x) { return x * x; }

int string2int(string str) {
    int res = 0;
    for (string::iterator iter = str.begin(); iter != str.end(); ++iter)
        res += *iter;
    return res;
}
string string2longerstring(string str) { return str + str; }

int main() {

    int t;
    cin >> t;
    while (t--) {
        int b1[10];
        for (int i = 0; i < 10; ++i)

            cin >> b1[i];
        A<int, 10> a1 = b1;
        cout << a1.sum(2, 6, int2squareint) << endl;
        cout << a1.sum(2, 6, int2string) << endl;

        string b2[4];
        for (int i = 0; i < 4; ++i)
            cin >> b2[i];

        A<string, 4> a2 = b2;
        cout << a2.sum(0, 3, string2int) << endl;
        cout << a2.sum(0, 3, string2longerstring) << endl;
    }
    return 0;
}