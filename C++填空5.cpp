#include <iostream>
#include <cmath>
using namespace std;

class Vector {
public:
    int length;
    int *array;
    Vector(const int& _length):length(_length){//构造函数
        array = new int[length];
    }
    Vector(const Vector& v){//复制构造函数
        length = v.length;
        array = new int[length];
        for(int i = 0; i < length; i++){
            array[i] = v.array[i];
        }
    }
    friend istream& operator >> (istream& is, Vector& v){//重载>>运算符
        for(int i = 0; i < v.length; i++){
            is >> v.array[i];
        }
        return is;
    }
    friend ostream& operator << (ostream& os, Vector v){//重载<<运算符
        for(int i = 0; i < v.length; i++){
            os << v.array[i];
            if(i != v.length - 1){
                os << ',';
            }
        }
        return os;
    }
    void operator += (const Vector& other){//重载+=运算符
        for(int i = 0; i < length; i++){
            array[i] += other.array[i];
        }
    }
    Vector operator + (const Vector& other){//重载+运算符
        Vector tmp(*this);
        for(int i = 0; i < length; i++){
            tmp.array[i] += other.array[i];
        }
        return tmp;
    }
    Vector operator * (const int &x){//重载*运算符
        Vector tmp(*this);
        for(int i = 0; i < length; i++){
            tmp.array[i] *= x;
        }
        return tmp;
    }
    double mo(){//定义mo函数
        double sum = 0;
        for(int i = 0; i < length; i++){
            sum += array[i] * array[i];
        }
        return sqrt(sum);
    }
    int operator[](int idx) const{//重载[]运算符
        return array[idx];
    }
    ~Vector(){//析构函数
        delete []array;
    }
};

int main() {
    int n, m, c;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m;
        Vector a(m), b(m);
        cin >> a >> b >> c;
        a += b;
        Vector d(b * c);
        cout << a + d << endl;
        cout << d * c << endl;
        cout << b.mo() << endl;
        cout << a[0] << endl;
        cout << endl;
    } return 0;
}