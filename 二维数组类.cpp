#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
public:
    int row, col;//二维数组的行和列
    int *array;
    Array2(int r, int c):row(r), col(c){
        if(row * col != 0)
            array = new int[row*col];//用一维数组模拟二维数组
        else
            array = NULL;
    }

    Array2(){
        row = 0;
        col = 0;
        array = NULL;
    }

    int *  operator [](int n){//重载[]运算符
        return &(array[n*col]);
    }
    int & operator()(int a, int b){//重载()运算符
        return array[col*a+b];
    }

    Array2 & operator = (const Array2 &a){//重载=运算符
        if(&a == this){
            return *this;
        }
        row = a.row;
        col = a.col;
        delete []array;
        if(row * col != 0) {
            array = new int[row * col];
            memcpy(array, a.array, sizeof(int) * row * col);
        }
        else
            array = NULL;
        return *this;
    }

    ~Array2(){
        delete []array;
    }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;
    b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}