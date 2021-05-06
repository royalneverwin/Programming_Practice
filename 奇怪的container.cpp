#include <iostream>
#include <string>
using namespace std;
template <class T>
class container{
public:
    T n;
    container(T num):n(num){}
    container operator + (const container<T> & other){
        return container<T>(n + other.n + other.n);
    }
    container operator + (const T& other){
        return container<T>(n + other);
    }
    friend ostream& operator << (ostream& os, container<T> c){
        os << c.n;
        return os;
    }
};
int main(){
    int n,m;
    cin >> n >> m;
    string s1,s2;
    cin >> s1 >> s2;
    container <int> a = n;
    container <int> b = m;
    cout<<a+b<<endl;
    cout<<a+m<<endl;
    container <string> sa = string(s1);
    container <string> sb = string(s2);
    cout<<sa+sb<<endl;
    cout<< sa + s2<<endl;
}