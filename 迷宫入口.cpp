#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;


int t;
int s;
int n;
map<int, int, greater<int>> ci; //注意这里用map！否则同一块能不能插入会检验多次，重复计算会超时!!!!
vector<vector<bool>> Map;
bool ans;


void dfs() {
    int x = 0;
    int y;
    int flag = 0;
    for (; x < s; x++) { //找最左上角的空格放砖
        for (y = 0; y < s; y++) {
            if (!Map[x][y]) {
                flag = 1;
                break;
            }
        }
        if (flag)
            break;
    }
    if(!flag){
        ans = true;
        return;
    }
    for (auto& p: ci) { //找能放的砖
        if (p.second != 0) {
            //检查能不能放这块砖
            flag = 1;
            if(x + p.first > s || y + p.first > s)
                continue;
            for (int j = 0; j < p.first; j++) {
                for (int k = 0; k < p.first; k++) {
                    if (Map[x + j][y + k]) {
                        flag = 0;
                        break;
                    }
                }
                if (!flag)
                    break;
            }
            if (flag) { //可以放
                p.second--;
                for (int j = 0; j < p.first; j++) {
                    for (int k = 0; k < p.first; k++) {
                        Map[x + j][y + k] = true;
                    }
                }
                dfs();
                if(ans)
                    return;
                //回溯
                p.second++;
                for (int j = 0; j < p.first; j++) {
                    for (int k = 0; k < p.first; k++) {
                        Map[x + j][y + k] = false;
                    }
                }
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> t;
    while(t--){
        ci.clear();
        ans = false;
        cin >> s >> n;
        for(int i = 1; i <= n; i++){
            int tmp;
            cin >> tmp;
            ci[tmp]++;
        }
        Map = vector<vector<bool>>(s, vector<bool>(s, false)); //vector初始化方法
        dfs();
        if(!ans)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }
    return 0;
}