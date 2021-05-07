#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
template<class T>
class Array{
public:
    virtual Array* operator [] (int K){};
    virtual operator T(){};
};
// 在此处补充你的代码
template <class T, int dim>
class DArray:public Array<T>{
public:
    vector<int> size;
    int total;
    T *array;
    int pos;
    int curpos;
    DArray(vector<int> _size):size(std::move(_size)){//构造函数
        total = 1;
        for(int i = 0 ; i < dim; i++){
            total *= size[i];
        }
        array = new T[total];
        pos = 0;
        curpos = 0;
    }
    ~DArray(){
        delete []array;
    }
    void init(){//构造init函数
        for(int i = 0; i < total; i++){
            cin >> array[i];
        }
    }
    DArray* operator [] (int K){
        int perK = 1;
        for(int i = curpos+1; i < dim; i++){
            perK *= size[i];
        }
        pos += K * perK;
        curpos = (curpos + 1) % dim;
        return this;
    };
//    friend ostream& operator << (ostream& os, const DArray<T, dim>& a){
//        os << a.array[a.pos];
//        a.pos = 0;
//        a.curpos = 0;
//        return os;
//    }
    operator T(){
        int tmp = pos;
        pos = 0;
        curpos = 0;
        return array[tmp];
    }
};
int main(){
    ios::sync_with_stdio(false); //主要是加快 cin 和 cout的速度
    int n=5,q; vector<int>size;
    for (int i=1;i<=n;i++){
        int si;
        cin>>si; size.push_back(si);
        //读入五维数组每一维的大小放入vector si中
    }
    DArray<int,5> A(size);
    A.init(); cin>>q;
    //对五维数组的访问次数
    for (int i=1;i<=q;i++){
        Array<int>*K=&A;
        //每一次访问输入 5 个数表示访问位置的下标
        for (int j=1;j<=n;j++){
            int x; cin>>x; K=(*K)[x];
        }
        cout<<(*K)<<endl;
    }

    n=10; size.clear();
    for (int i=1;i<=n;i++){
        int si; cin>>si; size.push_back(si);
        //读入十维数组每一维的大小放入vector si中
    }
    DArray<double,10> B(size);
    B.init(); cin>>q;
    //对十维数组的访问次数
    for (int i=1;i<=q;i++){
        Array<double>*K=&B;
        //每一次访问输入 10 个数表示访问位置的下标
        for (int j=1;j<=n;j++){
            int x; cin>>x; K=(*K)[x];
        }
        cout<<(*K)<<endl;
    }
}