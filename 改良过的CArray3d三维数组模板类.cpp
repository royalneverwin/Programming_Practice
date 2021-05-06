#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{//有了memset, 因此必须用一维数组实现, 用CArray2D单纯是为了可以实现两次对[]的重载
public:
    class CArray2D {
    public:
        T *array;
        int pos;//pos代表了第一次[]后array开始的位置
        int x, y, z;

        CArray2D(int X, int Y, int Z) {
            pos = 0;
            x = X;
            y = Y;
            z = Z;
            array = new T[x * y * z];
        }

        T *operator[](int idx) {
            return array + y * z * pos + z * idx;
        }
    }C2D;

    CArray3D(int X, int Y, int Z):C2D(X, Y, Z){}
    CArray2D& operator [](int idx){
        C2D.pos = idx;
        return C2D;
    }

    operator void *(){
        return C2D.array;
    }
};


CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
    for(int i = 0;i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < 5; ++k)
                cout << a[i][j][k] << "," ;
            cout << endl;
        }
    }
}
void PrintB()
{
    for(int i = 0;i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for(int j = 0; j < 2; ++j) {
            for(int k = 0; k < 2; ++k)
                cout << b[i][j][k] << "," ;
            cout << endl;
        }
    }
}

int main()
{

    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    PrintA();
    memset(a, -1, 60 * sizeof(int));        //注意这里
    memset(a[1][1], 0, 5 * sizeof(int));
    PrintA();

    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 2; ++j )
            for( int k = 0; k < 2; ++k )
                b[i][j][k] = 10.0 / (i + j + k + 1);
    PrintB();
    int n = a[0][1][2];
    double f = b[0][1][1];
    cout << "****" << endl;
    cout << n << "," << f << endl;

    return 0;
}