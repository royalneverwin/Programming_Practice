#include <iostream>
#include <string>
using namespace std;
string dec2bin(int x){
    char tmp[40];
    int index = 0;
    while(x > 1){
        tmp[index] = x % 2 + '0';
        x /= 2;
        index++;
    }
    tmp[index] = x + '0';
    index++;
    while(index < 31){
        tmp[index] = '0';
        index++;
    }
    tmp[index] = '\0';
    index--;
    string ans;
    ans.resize(31);//
    for(int i = index; i >= 0; i--){
        ans[index - i] = tmp[i];
    }
    return ans;
}
int main(){
    int n;
    cin >> n;
    while(n--) {
        int x;
        cin >> x;
        cout << dec2bin(x) << endl;
    }
    return 0;
}