#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <algorithm>
using namespace std;

//这里用dp！不用dfs


int m, n, s;
struct Project{
    int h;
    int c;
    int t;
    int cnt; //cnt = 1表示limit没玩；cnt = 0表示limit玩了；cnt = -1表示unlimit
    Project(int hh, int cc, int tt, int _cnt): h(hh), c(cc), t(tt), cnt(_cnt){}
};
vector<Project> project;
int dp[370][910]; //ih, j时间可以游玩的乐趣最大值，三维会MLE，用二维+覆盖



int Ticket(int day){
    if(day == 1)
        return 100;
    else if(day == 2)
        return 150;
    else if(day == 3)
        return 200;
    else{
        return 200 + Ticket(day - 3); //肯定先买天数最高的最划算
    }
}


void DP(int time, int money){
    int index = 0;
    while(index < project.size()) {
        for (int i = time; i >= 1; i--) {
            for (int j = money; j >= 0; j--) {
                if(project[index].cnt == 1){ //limit项目
                    if(i >= project[index].t && j >= project[index].c){ //能玩, 只能玩一遍
                        dp[i][j] = max(dp[i][j], project[index].h + dp[i-project[index].t][j - project[index].c]);
                    }
                }
                else{ //unlimit项目
                    int trial;
                    if(project[index].c == 0)
                        trial = i / project[index].t;
                    else
                        trial = min(i / project[index].t, j / project[index].c);
                    int ans = 0;
                    for(int k = 0; k <= trial; k++){
                        ans = max(ans, k * project[index].h + dp[i - project[index].t * k][j - project[index].c * k]);
                    }
                    dp[i][j] = ans;
                }
            }
        }
        index++;
    }
}


int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> m >> n >> s;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        int h;
        int c;
        int t;
        string name;
        cin >> h >> c >> t >> name;
        if(name == "limited")
            project.push_back(Project(h, c, t, 1));
        else
            project.push_back(Project(h, c, t, -1));
    }
    memset(dp, 0, sizeof(dp));
    DP(360, 900);
    for(int i = 1; i <= min(m, 15); i++){ //最多只能玩15天
        for(int j = 100; j <= s; j++){ //最少花100元门票
            int ticketCost = Ticket(i);
            int money = j;
            if(money < ticketCost)
                continue;
            money -= ticketCost;
            ans = max(ans, dp[i*24][money]);
        }
    }
    cout << ans << endl;
    return 0;
}