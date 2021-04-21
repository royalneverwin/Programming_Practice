#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;


stack<char> op;
stack<int> ans;


int num = 1;
int ifEnd = 0;


void Calculate(){
    char c;
    char tmp;
    int ans1, ans2;
    int n = scanf("%c", &c);
    while(1){//处理输入
        if(n == EOF){//所有输入都结束了, 将该表达式计算完后就结束程序 (注意最后一个表达式结尾无'\n')
            ifEnd = 1;
            break;
        }
        if(c == '\n'){
            break;
        }
        if(c == ' '){
            n = scanf("%c", &c);
            continue;
        }
        switch(c){
            case '('://输入'(', 直接入栈
                op.push(c);
                break;
            case ')'://输入')', 将栈中'('及之前的运算符全部出栈
                tmp = op.top();
                op.pop();
                while(tmp != '('){
                    if(tmp == '!'){
                        ans1 = ans.top();
                        ans.pop();
                        ans1 = !ans1;
                        ans.push(ans1);
                    } else if(tmp == '|'){
                        ans1 = ans.top();
                        ans.pop();
                        ans2 = ans.top();
                        ans.pop();
                        ans1 = ans1 | ans2;
                        ans.push(ans1);
                    } else if(tmp == '&'){
                        ans1 = ans.top();
                        ans.pop();
                        ans2 = ans.top();
                        ans.pop();
                        ans1 = ans1 & ans2;
                        ans.push(ans1);
                    }
                    tmp = op.top();
                    op.pop();
                }
                break;
            case '!'://输入!, 不需要出栈, 因为这个!一定最先被操作
                op.push(c);
                break;
            case '|'://输入'|', 若top是|或!或&, 出栈
                while (!op.empty() && op.top() != '(') {
                    tmp = op.top();
                    op.pop();
                    if (tmp == '!') {
                        ans1 = ans.top();
                        ans.pop();
                        ans1 = !ans1;
                        ans.push(ans1);
                    } else if (tmp == '|') {
                        ans1 = ans.top();
                        ans.pop();
                        ans2 = ans.top();
                        ans.pop();
                        ans1 = ans1 | ans2;
                        ans.push(ans1);
                    } else if (tmp == '&') {
                        ans1 = ans.top();
                        ans.pop();
                        ans2 = ans.top();
                        ans.pop();
                        ans1 = ans1 & ans2;
                        ans.push(ans1);
                    }
                }
                op.push(c);
                break;
            case '&'://输入'&', 若top是!或&, 出栈
                while (!op.empty() && op.top() != '(' && op.top() != '|') {
                    tmp = op.top();
                    op.pop();
                    if (tmp == '!') {
                        ans1 = ans.top();
                        ans.pop();
                        ans1 = !ans1;
                        ans.push(ans1);
                    } else if (tmp == '&') {
                        ans1 = ans.top();
                        ans.pop();
                        ans2 = ans.top();
                        ans.pop();
                        ans1 = ans1 & ans2;
                        ans.push(ans1);
                    }
                }
                op.push(c);
                break;
            case 'F':
                ans.push(0);
                break;
            case 'V':
                ans.push(1);
                break;
            default:
                break;
        }
        n = scanf("%c", &c);
    }
    while(!op.empty()){
        tmp = op.top();
        op.pop();
        if (tmp == '!') {
            ans1 = ans.top();
            ans.pop();
            ans1 = !ans1;
            ans.push(ans1);
        } else if (tmp == '|') {
            ans1 = ans.top();
            ans.pop();
            ans2 = ans.top();
            ans.pop();
            ans1 = ans1 | ans2;
            ans.push(ans1);
        } else if (tmp == '&') {
            ans1 = ans.top();
            ans.pop();
            ans2 = ans.top();
            ans.pop();
            ans1 = ans1 & ans2;
            ans.push(ans1);
        }
    }
    if(!ans.empty()) {
        cout << "Expression " << num << ": ";
        if (ans.top()) {
            cout << "V" << endl;
        } else {
            cout << "F" << endl;
        }
        while (!ans.empty())//初始化ans
            ans.pop();
        num++;
    }
}

int main(){
    char c = '0';
    int n = 1;
    while(!ifEnd){
        Calculate();
    }
    return 0;
}