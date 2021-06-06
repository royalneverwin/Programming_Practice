#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

stack<int> charPos;


int main(){
    char s[110];
    char ans[110];
    cin.getline(s, 110);
    while(s[0] != '\0'){
        for(int i = 0; i < strlen(s); i++){
            if(s[i] != '('  && s[i] != ')')
                ans[i] = ' ';
            else if(s[i] == '(')
                charPos.push(i);
            else{
                if(!charPos.empty()){
                    int pos = charPos.top();
                    ans[pos] = ans[i] = ' ';
                    charPos.pop();
                } else{
                    ans[i] = '?';
                };
            }
        }
        while(!charPos.empty()){
            int pos = charPos.top();
            ans[pos] = '$';
            charPos.pop();
        }
        ans[strlen(s)] = '\0';
        cout << ans << endl;
        cin.getline(s, 110);
    }
    return 0;
}