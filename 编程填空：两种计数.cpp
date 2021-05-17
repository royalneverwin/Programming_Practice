#include <iostream>
using namespace std;

class Counter {


private:
    static int nGlobalNumber;
    int nLocalNumber;
public:
// 在此处补充你的代码
    Counter(){
    nLocalNumber = 1;
    nGlobalNumber++;
}
    Counter(Counter& c){
    nGlobalNumber++;
    nLocalNumber = c.nLocalNumber;
}
    Counter(int n){
    nGlobalNumber++;
    nLocalNumber = n;
}
    ~Counter(){
    nGlobalNumber--;
}
    void add(int n) { nLocalNumber += n; }

    void PrintLocalNumber(){
        cout << nLocalNumber << endl;
    }
    static void PrintGlobalNumber() {
        cout << nGlobalNumber << endl;
    }

};
int Counter::nGlobalNumber = 0;

int main()
{
    Counter::PrintGlobalNumber();
    Counter b1, b2;
    Counter::PrintGlobalNumber();
    b1.PrintLocalNumber();
    b2.add(10);
    b2.PrintLocalNumber();
    Counter* b3 = new Counter(7);
    b3->PrintLocalNumber();
    Counter b4 = b2;
    b4.PrintLocalNumber();
    Counter::PrintGlobalNumber();
    if (b3 != NULL)
    {
        delete b3;
        b3 = NULL;
    }
    Counter::PrintGlobalNumber();


    return 0;
}