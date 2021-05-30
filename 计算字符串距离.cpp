#include <iostream>
#include <string>
#include <cstring>
using namespace std;


int compare[1010][1010]; //compare[i][j]代表s1[1:i]和s2[1:j]的距离


int main(){
    int n;
    cin >> n;
    while(n--){
        memset(compare, 0, sizeof(compare));
        string s1, s2;
        cin >> s1 >> s2;
        for(int i = 0; i <= s1.length(); i++){
            compare[i][0] = i;
        }
        for(int j = 0; j <= s2.length(); j++){
            compare[0][j] = j;
        }
        for(int i = 1; i <= s1.length(); i++){
            for(int j = 1; j <= s2.length(); j++){
                if(s1[i-1] == s2[j-1]){
                    compare[i][j] = compare[i-1][j-1];
                } else{
                    /*如果末尾字符不同，则有三种处理方式：修改、删除s1中的字符、删除s2中的字符，比较每种操作最少的操作数*/
                    compare[i][j] = min(1 + compare[i-1][j-1], 1 + compare[i-1][j]);
                    compare[i][j] = min(compare[i][j], 1 + compare[i][j-1]);
                }
            }
        }
        cout << compare[s1.length()][s2.length()] << endl;
    }
    return 0;
}