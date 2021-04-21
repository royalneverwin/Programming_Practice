#include <iostream>
#include <string>
using namespace std;
template <typename T, typename Pred>
void MyForeach(T* begin, T* end, Pred op){
    T* tmp = begin;
    do{
        op(*tmp);
        tmp++;
    }while(tmp != end);
}


void Print(string s)
{
    cout << s;
}
void Inc(int & n)
{
    ++ n;
}


string Array[100];
int a[100];
int main() {
    int m,n;
    while(cin >> m >> n) {
        for(int i = 0;i < m; ++i)
            cin >> Array[i];
        for(int j = 0; j < n; ++j)
            cin >> a[j];
        MyForeach(Array,Array+m,Print);
        cout << endl;
        MyForeach(a,a+n,Inc);
        for(int i = 0;i < n; ++i)
            cout << a[i] << ",";
        cout << endl;
    }
    return 0;
}