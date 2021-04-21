#include <iostream>
#include <set>
using namespace std;

class Rectangle{
public:
    int a, b;
    Rectangle(int m, int n):a(m),b(n){}
    int S() const{
        return a*b;
    }
    int C() const{
        return 2*(a+b);
    }
    friend ostream &operator << (ostream &os, Rectangle r){
        os << r.S() << ' ' << r.C();
        return os;
    }
    bool operator < (const Rectangle &r) const{
        return (S() == r.S() ? C() > r.C() :S() > r.S());
    }

};

//bool operator < (Rectangle r1, Rectangle r2){
//    return (r1.S() == r2.S() ? r1.C() > r2.C() :r1.S() > r2.S());
//}


struct Comp {
    bool operator ()(Rectangle r1, Rectangle r2) {
        return (r1.C() == r2.C() ? r1.S() < r2.S() : r1.C() < r2.C());
    }
};


int main() {
    multiset<Rectangle> m1;
    multiset<Rectangle, Comp> m2;
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        m1.insert(Rectangle(a, b));
        m2.insert(Rectangle(a, b));
    }
    for (multiset<Rectangle>::iterator it = m1.begin(); it != m1.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    for (multiset<Rectangle>::iterator it = m2.begin(); it != m2.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}