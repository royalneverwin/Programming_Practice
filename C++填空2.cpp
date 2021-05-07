#include <iostream>
using namespace std;

class num {
private:
    int d;
public:
    num(int _d = 0): d(_d) {}

    num(const num& u) {
        d = u.d;
        cout << "Copy Construct is called!" << endl;
    }

    num& operator =(const num &u) {
        d = u.d;
        cout << "Copy Assignment is called!" << endl;
        return *this;
    }

    num& operator =(num &&u) {
        d = u.d;
        u.d = 0;
        return *this;
    }

    num(num &&u) {
        d = u.d;
        u.d = 0;
    }

    void print() {
        cout << d;
    }
} ;

class A {
public:
    num d;

    A(const int _d = 0): d(_d) {}

    A(const A& u) {
        d = u.d;
        cout << "Copy Construct is called!" << endl;
    }

    A& operator =(const A &u) {
        d = u.d;
        cout << "Copy Assignment is called!" << endl;
        return *this;
    }
    void swap(A &b){
        num tmp(move(d));
        d = move(b.d);
        b.d = move(tmp);
    }
} ;

int main() {
    int x, y;
    while (cin >> x >> y) {
        A a(x), b(y);
        a.d.print(); cout << ',';
        b.d.print(); cout << endl;
        a.swap(b);
        a.d.print(); cout << ',';
        b.d.print(); cout << endl;
    }
    return 0;
}