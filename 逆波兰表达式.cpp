#include <iostream>
using namespace std;


//读入一个逆波兰表达式并计算其值
double exp(){
   char s[20];//每个数字和符号之间有间隔
   cin >> s;
   switch (s[0]){
       case '+':return exp() + exp();
       case '-': return exp() - exp();
       case '*':return exp() * exp();
       case '/':return exp() / exp();
       default:return atof(s);
       break;
   }
}
//用递归解决递归形式的问题
int main(){
    printf("%lf", exp());
    return 0;
}