#include <iostream>
#include <cstring>
#include <string>
using namespace std;
bool substr[110][110]; //判断从i到j是不是回文子串（包括头尾）
int n;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n;
    while(n--){
        string s;
        cin >> s;
        memset(substr, 0, sizeof(substr));
        int ansx = 0;
        int ansy = 0;
        for(int i = 0; i < s.length(); i++){
            substr[i][i] = true;
        }
        bool first = true;
        for(int i = 0; i < s.length()-1; i++){
            if(s[i] == s[i+1]) {
                if(first){
                    ansx = i;
                    ansy = i+1;
                    first = false;
                }
                substr[i][i + 1] = true;
            }
            else {
                substr[i][i + 1] = false;
            }
        }
        for(int l = 3; l <= s.length(); l++){
            bool flag = false;
            for(int i = 0; i < s.length() - l + 1; i++){ //i是开头
                if(substr[i+1][i+l-2] && s[i] == s[i+l-1]){
                    if(!flag) {
                        ansx = i;
                        ansy = i + l - 1;
                    }
                    substr[i][i+l-1] = true;
                    flag = true;
                }
                else
                    substr[i][i+l-1] = false;
            }
        }
        string substrS = s.substr(ansx, ansy - ansx + 1);
        cout << substrS << endl;
    }
    return 0;
}