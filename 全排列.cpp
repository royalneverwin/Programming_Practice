#include <iostream>
#include <string>
using namespace std;


string old;


void Arrange(int n){//对string tmp从n开始全排列
    char tmpC;
    string curOld = old;
    if(n == old.length() - 1){
        cout << old << endl;
        return;
    }
    for(int i = n; i < old.length(); i++){
        tmpC = old[i];
        for(int j = i; j > n; j--){//注意全排列的定义！交换元素时不是简单的对换
            old[j] = old[j-1];
        }
        old[n] = tmpC;
        Arrange(n+1);
        old = curOld;//下一次Arrange时需要还原tmp
    }
}
int main(){
    cin >> old;
    Arrange(0);
    return 0;
}