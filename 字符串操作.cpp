#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
using namespace std;
#define DEBUG


vector<string> stringArray;

int getInteger(string command, int& index1, int &index2);
string getString(string command, int& index1, int &index2);

bool ifInteger(string &s){
    if(s.length() > 5){
        return false;
    } else{
        for(auto &i: s){
            if(i < '0' || i > '9'){
                return false;
            }
        }
        return true;
    }
}


string Copy(int n, int x, int l){//取出第N个字符串第X个字符开始的长度为L的字符串
    string cur = stringArray[n-1];
    return cur.substr(x, l);
}

string Add(string s1, string s2){//判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。
    if(ifInteger(s1) && ifInteger(s2)){//进行整数加法
        int num1 = atoi(s1.c_str());
        int num2 = atoi(s2.c_str());
        num1 += num2;
        ostringstream outputString;
        outputString << num1;
        return outputString.str();
    } else{//进行字符串加法
        return s1 + s2;
    }
}

int Find(string s, int n){//在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
    string cur = stringArray[n-1];
    int pos = cur.find(s);
    if(pos != string::npos){
        return pos;
    } else{
        return cur.length();
    }
}

int Rfind(string s, int n){//在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
    string cur = stringArray[n-1];
    int pos = cur.rfind(s);
    if(pos != string::npos){
        return pos;
    } else{
        return cur.length();
    }
}

void Insert(string s, int n, int x){//在第N个字符串的第X个字符位置中插入S字符串。
    string &cur = stringArray[n-1];
    cur.insert(x, s);
}

void Reset(string s, int n){//将第N个字符串变为S
    stringArray[n-1] = s;
}

void Print(int n){//打印输出第N个字符串。
    cout << stringArray[n-1] << endl;
}

void Printall(){//打印出所有字符串
    for(auto tmps: stringArray){
        cout << tmps << endl;
    }
}

int getInteger(string command, int& index1, int& index2){//可能是数字、find和rfind函数
    string curCommand;
    for(int i = index1; i < command.length(); i++) {
        if (command[i] == ' ' || command[i] == '\0') {
            index2 = i;
            break;
        }
    }
    curCommand = command.substr(index1, index2 - index1);
#ifdef DEBUG
#endif
    index1 = index2 + 1;
    if(curCommand == "find"){
        string s = getString(command, index1, index2);
        int n = getInteger(command, index1, index2);
        return Find(s, n);
    } else if(curCommand == "rfind"){
        string s = getString(command, index1, index2);
        int n = getInteger(command, index1, index2);
        return Rfind(s, n);
    } else{//是个数字
        return atoi(curCommand.c_str());
    }
}

string getString(string command, int& index1, int &index2){//可能是字符串、copy和add函数
    string curCommand;
    for(int i = index1; i < command.length(); i++) {
        if (command[i] == ' ' || command[i] == '\0') {
            index2 = i;
            break;
        }
    }
    curCommand = command.substr(index1, index2 - index1);
#ifdef DEBUG
#endif
    index1 = index2 + 1;
    if(curCommand == "copy"){
        int n = getInteger(command, index1, index2);
        int x = getInteger(command, index1, index2);
        int l = getInteger(command, index1, index2);
        return Copy(n, x, l);
    } else if(curCommand == "add"){
        string s1 = getString(command, index1, index2);
        string s2 = getString(command, index1, index2);
        return Add(s1, s2);
    } else{//是字符串
        return curCommand;
    }
}

void ManageCommand(string command){
    int index1 = 0;
    int index2 = 0;
    string basicCommand;
    for(int i = 0; i <= command.length(); i++) {
        if (command[i] == ' ' || command[i] == '\0') {
            index2 = i;
            break;
        }
    }
    basicCommand = command.substr(index1, index2 - index1);
    index1 = index2 + 1;
        /*copy, add, find, rfind不会出现在basicCommand里*/
    if(basicCommand == "insert"){
        string s = getString(command, index1, index2);
        int n = getInteger(command, index1, index2);
        int x = getInteger(command, index1, index2);
        Insert(s, n, x);
    } else if(basicCommand == "reset"){
        string s = getString(command, index1, index2);
        int n = getInteger(command, index1, index2);
        Reset(s, n);
    } else if(basicCommand == "print"){
        int n = getInteger(command, index1, index2);
        Print(n);
    } else if(basicCommand == "printall"){
        Printall();
    } else if(basicCommand == "over"){
        exit(0);
    } else{
        cout << "Wrong management: " << basicCommand << endl;
        exit(1);
    }
}


int main(){
    int n;
    cin >> n;
    string tmp;
    for(int i = 0; i < n; i++){
        cin >> tmp;
        stringArray.push_back(tmp);
    }
    cin.ignore();//将cin流中'\n'忽略
    string command;
    while(getline(cin, command)){
#ifdef DEBUG
#endif
        ManageCommand(command);
    }
    return 0;
}