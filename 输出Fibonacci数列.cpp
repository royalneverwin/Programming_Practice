#include <iostream>
#include <iterator>
using namespace std;

template<class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for(; s != e; ++s, ++x)
        *x = *s;
}
class Fib{
    public:
    int num;
    int prevNum;
    int n;
    Fib(int N):n(N){
        num = 1;
        prevNum = 1;
        if(n == 1){
            num = 1;
            prevNum = 0;
        } else if(n == 2){
            num  = 1;
            prevNum = 0;
        } else{
            num = 1;
            prevNum = 1;
            int tmp;
            for(int i = 3; i <= n; i++){
                tmp = num;
                num = num + prevNum;
                prevNum = tmp;
            }
        }
    }

    bool operator != (const Fib& other) const{
        return n != other.n;
    }
    void operator ++ (){
        int tmp;
        tmp = num;
        num = num + prevNum;
        prevNum = tmp;
        n++;
    }

    int operator *() const{
        return num;
    }
};

int main() {
    while(true) {
        int n;
        cin >> n;
        if(n == 0)
            break;

        Fib f1(1), f2(n);
        ostream_iterator<int> it(cout, " ");
        Copy(f1, f2, it);
        cout << endl;
    }
    return 0;
}