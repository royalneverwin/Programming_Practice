#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, x;
int A[10];
bool horse[10];
int ans[10];
void dfs(int which, int win){
    if(n - which + win <= n / 2){ //不可能成功，剪枝
        return;
    }
    if(which == n){ //已经遍历完了
        for(int i = 0; i < n; i++){
            cout << ans[i] << ' ';
        }
        cout << endl;
        return;
    }
    for(int i = 1; i <= n; i++){
        if(!horse[i]){
            ans[which] = i;
            horse[i] = true;
            if(i >= A[which] + x){
                dfs(which + 1, win + 1);
            }
            else{
                dfs(which + 1, win);
            }
            //回溯
            horse[i] = false;
        }
    }
}
int main() {
    cin >> n >> x;
    int maxLevel = 0;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        maxLevel = max(maxLevel, A[i]);
    }
    memset(horse, 0, sizeof(horse));
    dfs(0, 0);
    return 0;
}