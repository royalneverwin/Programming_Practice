#include <iostream>
using namespace std;
class MyCin
{
public:
    int flag;
    MyCin(){
        flag = 1;
    }
     operator bool(){
        return flag;
    }
    MyCin &operator >> (int &n){
        cin >> n;
        if(n == -1)
            flag = 0;
        return *this;
    }
};


int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2)
        cout  << n1 << " " << n2 << endl;
    return 0;
}