#include <iostream>
using namespace std;

class A {
public:
    int n;
    A(int num):n(num){}
    A& getValue(){
        return *this;
    }
    friend ostream & operator << (ostream &os, A tmp){
        os << tmp.n;
        return os;
    }
    A &operator += (A tmp){
        n += tmp.n;
        return *this;
    }
    A &operator -=(int tmp){
        n -= tmp;
        return *this;
    }

};

int main() {
    int t;
    cin >> t;
    while(t-- ) {
        int m,n,k;
        cin >> m >> n >> k;
        A a(m);
        A b = a;
        cout << b << endl;
        cout << (a += b -= n) << endl;
        cout << a.getValue() << endl;
        a.getValue() = k;
        cout << a << endl;
    }
    return 0;
}