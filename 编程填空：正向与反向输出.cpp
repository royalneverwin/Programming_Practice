#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
class C1{
// 在此处补充你的代码
public:
    int size;
    int* v;
    C1(C1 const &c):size(c.size){
        v = new int[size];
        for(int i = 0; i < size; i++){
            v[i] = c.v[i];
        }
    }
    C1(int _size, vector<int> _v):size(_size){
        v = new int[size];
        for(int i = 0; i < size; i++){
            v[i] = _v[i];
        }
    }
    int* operator * () const{
        return v;
    }
    int& operator[](int index) const{
        return v[size - index - 1];
    }
};

int main()
{
    vector<int> v;
    int p;
    int size;
    int k;
    cin >> k;
    while(k--){
        cin >> size;
        v.clear();
        for(int i = 0; i < size; ++i){
            cin >> p;
            v.push_back(p);
        }
        C1 o1 = C1(size,v);
        ostream_iterator<int> it(cout,"---");
        copy(*o1, (*o1)+size, it);
        cout<<endl;
        for(int i = 0; i < size; ++i){
            o1[i]*=2;
            cout<<o1[i]<<"***";
        }
        cout<<endl;
    }

}