#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

//正常表达式计算
//表达式 > 项 > 因子 > 表达式/整数
int factor_value();
int term_value();
int expression_value();


int factor_value(){//因子的值
    int result = 0;
    char c = cin.peek();
    if(c == '('){
        cin.get();
        result = expression_value();
        cin.get();
    }
    else{
        while(isdigit(c)){//读整数的方式！！！
            result = 10 * result + c - '0';
            cin .get();
            c = cin.peek();
        }
    }
    return result;
}


int term_value(){//项的值
    int result = factor_value();
    while(true){
        char op = cin.peek();
        if(op == '*' || op == '/'){
            cin.get();
            int value = factor_value();
            if(op == '*') result *= value;
            else result /= value;
        }
        else break;
    }
    return result;
}


int expression_value(){//表达式的值
    int result = term_value();
    bool more = true;
    while(more){
        char op = cin.peek();//看第一个字符，不取走
        if(op == '+' || op == '-'){
            cin .get();//从输入中取走一个字符
            int value = term_value();
            if(op == '+') result += value;
            else result -= value;
        }
        else more = false;
    }
    return result;
}


int main(){
    cout << expression_value() << endl;
    return 0;
}