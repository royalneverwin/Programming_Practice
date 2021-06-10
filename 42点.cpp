#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


vector<int> num;
int n;


void dfs(){
    if(num.size() == 1){
        if(num[0] == 42){
            cout << "YES" << endl;
            exit(0);
        }
        return;
    }
    if(num.size() == 2){
        if(num[0] + num[1] == 42 || num[0] - num[1] == 42 || num[1] - num[0] == 42 || num[1] * num[0] == 42){
            cout << "YES" << endl;
            exit(0);
        }
        if(num[0] != 0 && num[1] / num[0] == 42){
            cout << "YES" << endl;
            exit(0);
        }
        if(num[1] != 0 && num[0] / num[1] == 42){
            cout << "YES" << endl;
            exit(0);
        }
        return;
    }
    //任取两个数
    int num1, num2, result;
    vector<int> tmp = num;
    for(int i = 0; i < tmp.size()-1; i++){
        for(int j = i+1; j < tmp.size(); j++){
            num1 = tmp[i];
            num2 = tmp[j];
            num.erase(find(num.begin(), num.end(), num1));
            num.erase(find(num.begin(), num.end(), num2));
            result = num1 + num2;
            num.push_back(result);
            dfs();
            num.erase(find(num.begin(), num.end(), result));//回溯
            result = num1 - num2;
            num.push_back(result);
            dfs();
            num.erase(find(num.begin(), num.end(), result));//回溯
            result = num2 - num1;
            num.push_back(result);
            dfs();
            num.erase(find(num.begin(), num.end(), result));//回溯
            result = num1 * num2;
            num.push_back(result);
            dfs();
            num.erase(find(num.begin(), num.end(), result));//回溯
            if(num2 != 0) {
                result = num1 / num2;
                num.push_back(result);
                dfs();
                num.erase(find(num.begin(), num.end(), result));//回溯
            }
            if(num1 != 0) {
                result = num2 / num1;
                num.push_back(result);
                dfs();
                num.erase(find(num.begin(), num.end(), result));//回溯
            }
            //回溯
            num.push_back(num1);
            num.push_back(num2);
        }
    }
}


int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        int t;
        cin >> t;
        num.push_back(t);
    }
    dfs();
    cout << "NO" << endl;
    return 0;
}