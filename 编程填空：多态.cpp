#include <iostream>
using namespace std;

class Base {
public:
    virtual Base& fun() { cout << "base fun" << endl; return *this; }
    virtual Base& foo() { cout << "base foo" << endl; return *this; }
};

class Derived: public Base {
public:
    Base& fun() { cout << "derived fun" << endl; return *this; }
    Base& foo() { cout << "derived foo" << endl; return *this; }
};

Base& foo();
Base& fun();
// 在此处补充你的代码
Base &foo(){
    Derived* tmp = new Derived();
    tmp->foo();
    return *tmp;
}
Base &fun(){
    Base* tmp = new Base();
    tmp->fun();
    return *tmp;
}
int main() {
    foo().fun().foo();
    fun().foo().fun();
    return 0;
}