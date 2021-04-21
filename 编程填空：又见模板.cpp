#include <iostream>
#include <string>
using namespace std;

template <class T1, int s>
class A{
public:
    T1 *a;
    A(T1 *b){
        a = new T1[s];
        for(int i = 0; i < s; i++){
            a[i] = b[i];
        }
    }
    T1& operator [](int index){
        return a[index];
    }
    T1 sum(){
        T1 tmp = a[0];
        for(int i = 1; i < s; i++) {
            tmp += a[i];
        }
        return tmp;
    }
};
int main() {

    int t;
    cin >> t;
    while( t -- ) {
        int b1[10];
        for(int i = 0;i < 10; ++i)

            cin >> b1[i];
        A<int, 10> a1 = b1;
        cout << a1[2] << endl;


        double b2[5] ;
        for(int i = 0;i < 5; ++i)
            cin >> b2[i];

        A<double, 5> a2 = b2;
        cout << a2.sum() << endl;


        string b3[4] ;
        for(int i = 0;i < 4; ++i)
            cin >> b3[i];

        A<string, 4> a3 = b3;
        cout << a3.sum() << endl;
    }
    return 0;
}