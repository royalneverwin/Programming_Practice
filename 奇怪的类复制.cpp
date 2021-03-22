#include <iostream>
using namespace std;
class Sample {
public:
    int v;
    Sample(int a){
        v = a;
    }
    Sample(const Sample & a){
        v = a.v + 2;
    }
    Sample(){
        v = 0;
    }
};
void PrintAndDouble(Sample o)//如果不用const Sample &o，系统会调用一遍复制构造函数传递一个虚拟对象，因此结果会+2！
{
    cout << o.v;
    cout << endl;
}
int main()
{
    Sample a(5);
    Sample b = a;
    PrintAndDouble(b);
    Sample c = 20;
    PrintAndDouble(c);
    Sample d;
    d = a;
    cout << d.v;
    return 0;
}