#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


int cnt = 1;


void CheckDir(string& name, int layer){//check第layer层的文件结构，这一层的名字叫name
    for(int i = 0; i < layer; i++){
        cout << "|     ";
    }
    cout << name << endl;
    vector<string> file;
    string l;
    while(1) {
        cin >> l;
        if (l == "]") {//代表这一层结束了
            break;
        }
        if (l[0] == 'd') {
            CheckDir(l, layer + 1);
        } else {
            file.push_back(l);
        }
    }
    sort(file.begin(), file.end());
    for(auto &f: file){
        for(int i = 0; i < layer; i++){
            cout << "|     ";
        }
        cout << f << endl;
    }
}


int CheckAll(){
    int message;
    string l;
    cin >> l;
    if(l == "#"){
        return 0;
    }
    cout << "DATA SET " << cnt << ':' << endl;
    cout << "ROOT" << endl;
    vector<string> file;
    while(1) {
        if (l == "*") {//代表这一样例结束了
            break;
        }

        if(l[0] == 'd'){
            CheckDir(l, 1);
        }
        else{
            file.push_back(l);
        }
        cin >> l;
    }
    sort(file.begin(), file.end());
    for(auto &f: file){
        cout << f << endl;
    }
    return 1;
}


int main(){
    while(CheckAll()){
        cout << endl;
        cnt++;
    }
    return 0;
}