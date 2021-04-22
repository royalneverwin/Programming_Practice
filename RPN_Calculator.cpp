#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;
#define DEBUG

stack<double> fnum;
priority_queue<double, vector<double>, greater<double>> storage;


void Operator(char op){
    double num1, num2;
    num2 = fnum.top();
    fnum.pop();
    num1 = fnum.top();
    fnum.pop();
    switch(op){
        case '+':
            num1 = num1 + num2;
            break;
        case '-':
            num1 = num1 - num2;
            break;
        case '*':
            num1 = num1 * num2;
            break;
        case '/':
            num1 = num1 / num2;
            break;
        case '^':
            num1 = pow(num1, num2);
            break;
        default:
            cout << "something is wrong" << endl;
            break;
    }
    fnum.push(num1);
}


void ManageOp(string& op) {
    if (op != "+" && op != "-" && op != "*" && op != "/" && op != "^") {//遇到数字就入栈
        fnum.push(atof(op.c_str()));
    } else{
        Operator(op[0]);
    }
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n;//Storage Count
    int index1, index2;
    double initialStorage;
    string expression;
    string op;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> initialStorage;
        storage.push(initialStorage);
    }
    cin.ignore();
    while(getline(cin, expression)){
        while(!fnum.empty()){
            fnum.pop();
        }
        if(expression[0] == 'w'){
            break;
        }
        index1 = 0;
        index2 = expression.length();
        for(int i = 0; i <= expression.length(); i++){
            if(expression[i] == ' ' || expression[i] == '\0'){
                index2 = i;
                op = expression.substr(index1, index2 - index1);
                index1 = index2 + 1;
                if(op == "="){
                    printf("%e\n", fnum.top());
                    storage.pop();
                    storage.push(fnum.top());
                    break;
                } else {
                    ManageOp(op);
                }
            }
        }
    }
    printf("\n");
    int count = 0;
    while(!storage.empty()){//输出存储的数字
        printf("%e", storage.top());
        storage.pop();
        count++;
        if(count == 10){//10个一行
            count = 0;
            printf("\n");
        } else{
            printf(" ");
        }
    }
    return 0;
}

