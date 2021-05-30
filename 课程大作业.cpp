#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct Node{
    int pre; //上一个状态的下标
    int minScore; //当前状态的最低扣分
    int last; //当前状态下最后一个完成的作业
    int finishDay; //作业last完成的时间
};
struct Node dp[(1 << 16) + 10];
struct Course{
    string name;
    int ddl;
    int cost;
};
struct Course allCourse[16];


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        vector<string> ans;
        int n;
        cin >> n;
        memset(dp, 0, sizeof(dp));
        dp[0].pre = -1;
        dp[0].minScore = 0;
        dp[0].last = -1;
        dp[0].finishDay = 0;
        for(int i = 0; i < n; i++) {
            cin >> allCourse[i].name >> allCourse[i].ddl >> allCourse[i].cost;
            //初始化dp
            dp[(1 << i)].pre = -1;
            dp[(1 << i)].minScore = max(allCourse[i].cost - allCourse[i].ddl, 0);
            dp[(1 << i)].last = i;
            dp[(1 << i)].finishDay = allCourse[i].cost;
        }
        //填充dp
        for(int i = 1; i < (1 << n); i++){
            int flag = 0;
            for(int j = 0; j < n; j++){
                int tmpMin;
                if(!flag)
                    tmpMin = 1 << 30;
                else
                    tmpMin = dp[i].minScore;
                if(i & (1 << j)){
                    flag = 1;//dp[i]表示的状态包括了课程j
                    if(tmpMin > dp[i ^ (1 << j)].minScore + max(dp[i ^ (1 << j)].finishDay + allCourse[j].cost - allCourse[j].ddl, 0)){ //更新
                        if((i ^ (1 << j)) == 0)
                            dp[i].pre = -1;
                        else
                            dp[i].pre = i ^ (1 << j);
                        dp[i].last = j;
                        dp[i].minScore = dp[i ^ (1 << j)].minScore + max(dp[i ^ (1 << j)].finishDay + allCourse[j].cost - allCourse[j].ddl, 0);
                        dp[i].finishDay = dp[i ^ (1 << j)].finishDay + allCourse[j].cost;
                    } else if(tmpMin == dp[i ^ (1 << j)].minScore + max(dp[i ^ (1 << j)].finishDay + allCourse[j].cost - allCourse[j].ddl, 0)){ //看字典序哪个小，在更新
                        vector<string> s1;
                        vector<string> s2;
                        int end1 = dp[i].pre;
                        s1.push_back(allCourse[dp[end1].last].name);
                        while(dp[end1].pre != -1){
                            end1 = dp[end1].pre;
                            s1.push_back(allCourse[dp[end1].last].name);
                        }
                        int end2 = i^(1 << j);
                        s2.push_back(allCourse[dp[end2].last].name);
                        while(dp[end2].pre != -1){
                            end2 = dp[end2].pre;
                            s2.push_back(allCourse[dp[end2].last].name);
                        }
                        reverse(s1.begin(), s1.end());
                        reverse(s2.begin(), s2.end());
                        string compare1;
                        string compare2;
                        for(auto &tmp: s1)
                            compare1.append(tmp);
                        for(auto &tmp: s2)
                            compare2.append(tmp);
                        if(s2 < s1) {//当新的字典序更小，就更换
                            if((i ^ (1 << j)) == 0)
                                dp[i].pre = -1;
                            else
                                dp[i].pre = i ^ (1 << j);
                            dp[i].last = j;
                            dp[i].minScore = dp[i ^ (1 << j)].minScore + max(dp[i ^ (1 << j)].finishDay + allCourse[j].cost - allCourse[j].ddl, 0);
                            dp[i].finishDay = dp[i ^ (1 << j)].finishDay + allCourse[j].cost;
                        }
                    }
                }
            }
        }
        int end = (1 << n) - 1;
        cout << dp[end].minScore << endl;
        ans.push_back(allCourse[dp[end].last].name);
        while(dp[end].pre != -1){
            end = dp[end].pre;
            ans.push_back(allCourse[dp[end].last].name);
        }
        reverse(ans.begin(), ans.end());
        for(auto &name: ans)
            cout << name << endl;
    }
    return 0;
}