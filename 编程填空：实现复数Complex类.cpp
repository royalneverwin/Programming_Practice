#include <iostream>
using namespace std;
class Complex{
public:
    int a, b;
    Complex(const int r = 0, const int i = 0):a(r), b(i){}
    Complex(const char *s){
        a = s[0] - '0';
        b = s[2] - '0';
    }
    friend ostream& operator << (ostream &os, Complex c){
        if(c.a != 0 && c.b != 0){
            os << c.a << '+' << c.b << 'i';
        } else if(c.a == 0 && c.b != 0){
            os << c.b << 'i';
        } else if(c.b == 0 && c.a != 0){
            os << c.a;
        } else{
            os << 0;
        }
        return os;
    }
    Complex operator + (Complex c) const{
        return Complex(a+c.a, b+c.b);
    }
    Complex operator - (Complex c) const{
        return Complex(a-c.a, b-c.b);
    }
    Complex operator * (Complex c) const{
        return Complex(a*c.a - b*c.b, a*c.b + b*c.a);
    }
    void operator += (Complex c) {
        a += c.a;
        b += c.b;
    }
    void operator -= (Complex c) {
        a -= c.a;
        b -= c.b;
    }
    void operator *= (Complex c) {
        *this = (*this) * c;
    }
};
int main() {
    Complex c1;
    Complex c2("3+2i"); // 用字符串初始化时，只需考虑"a+bi"的形式，其中a和b都是1位数字
    Complex c3(c2);
    Complex c4(-15);
    cout << c2 << endl;
    cout << c3 << endl;
    cout << c4 << endl;
    cout << c2 + c4 << endl;
    cout << c2 - c3 << endl;
    cout << c2 * c3 << endl;
    c2 += c4;
    cout << c2 << endl;
    c2 -= -12;
    cout << c2 << endl;
    c3 *= c3;
    cout << c3 << endl;
    return 0;
}