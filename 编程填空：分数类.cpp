#include <iostream>
using namespace std;
int gcd(int x, int y){
    return x%y==0?y:gcd(y,x%y);
}
class Fraction
{
    int num, den;
public:
// 在此处补充你的代码

    Fraction(int _num, int _den):num(_num), den(_den){}

    Fraction(int _num):num(_num), den(1){}


    friend ostream& operator << (ostream& os, Fraction f){//这里不要想太多！直接无脑输出就行，因为答案确实就是无脑输出....
        os << f.num << '/' << f.den;
        return os;
    }

    void operator /= (Fraction other){
        num *= other.den;
        den *= other.num;
        if(num != 0) {
            int g = gcd(num, den);
            num /= g;
            den /= g;
        }
    }
    void operator *= (Fraction other){
        num *= other.num;
        den *= other.den;
        if(num != 0) {
            int g = gcd(num, den);
            num /= g;
            den /= g;
        }
    }
    Fraction operator * (Fraction other) const{
        int tmpNum, tmpDen;
        tmpNum = num * other.num;
        tmpDen = den * other.den;
        if(tmpNum != 0) {
            int g = gcd(tmpNum, tmpDen);
            tmpNum /= g;
            tmpDen /= g;
        }
        Fraction tmp(tmpNum, tmpDen);
        return tmp;
    }
    Fraction operator / (Fraction other) const{
        int tmpNum, tmpDen;
        tmpNum = num * other.den;
        tmpDen = den * other.num;
        if(tmpNum != 0){
            int g = gcd(tmpNum, tmpDen);
            tmpNum /= g;
            tmpDen /= g;
        }
        Fraction tmp(tmpNum, tmpDen);
        return tmp;
    }
    operator float(){
    return num / float(den);
    }
};

int main() {
    int a,b,c;
    cin >> a >> b >> c;
    Fraction f(a, b), g(c);
    f *= g;
    cout << f << endl;
    f /= g;
    cout << f << endl;
    f = f * f;
    cout << f << endl;
    f = f / g;
    cout << f << endl;
    cout << (float) f << endl;
    return 0;
}