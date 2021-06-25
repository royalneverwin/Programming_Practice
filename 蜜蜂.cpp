#include <iostream>
#include <cstring>
using namespace std;


long long ans[51][51]; //从i到j的总数
long long dfs(int a, int b){
    if(ans[a][b] != 0){
        return ans[a][b];
    }
    if(a == b){
        return ans[a][b] = 0;
    }
    else if(a == b-1){
        return ans[a][b] = 1;
    }
    else if(a == b-2){
        return ans[a][b] = 2;
    }
    else{
        return ans[a][b] = dfs(a+1, b) + dfs(a+2, b);
    }
}
int main(){
    int n;
    cin >> n;
    int a, b;
    while(n--){
        memset(ans, 0, sizeof(ans));
        cin >> a >> b;
        cout << dfs(a,  b) << endl;
    }
    return 0;
}